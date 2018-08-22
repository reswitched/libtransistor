#include<libtransistor/waiter.h>

#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/mutex.h>

#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct wait_record_t {
	handle_t handle;
	void *data;
	bool (*signal)(void *data, handle_t handle);
	uint64_t age;
	wait_record_t *prev;
	wait_record_t *next;
	bool is_being_signalled;
	bool destroy_flag;
};

struct waiter_t {
	trn_mutex_t mutex;
	wait_record_t list;
	
	size_t handle_buffer_length;
	handle_t *handle_buffer;

	size_t record_buffer_length;
	wait_record_t **record_buffer;
};

waiter_t *waiter_create() {
	waiter_t *waiter = malloc(sizeof(*waiter));
	if(waiter == NULL) {
		return NULL;
	}
	
	memset(waiter, 0, sizeof(*waiter));
	trn_mutex_create(&waiter->mutex);
	return waiter;
}

wait_record_t *waiter_add(waiter_t *waiter, handle_t handle, bool (*signal)(void *data, handle_t handle), void *data) {
	wait_record_t *record = malloc(sizeof(*record));
	if(record == NULL) {
		return NULL;
	}

	memset(record, 0, sizeof(*record));
	record->handle = handle;
	record->data = data;
	record->signal = signal;
	record->age = 0;

	trn_mutex_interrupt_lock(&waiter->mutex);
	record->prev = &waiter->list;
	record->next = waiter->list.next;
	if(record->next) {
		record->next->prev = record;
	}
	waiter->list.next = record;
	trn_mutex_unlock(&waiter->mutex);

	return record;
}

static int record_compare(const void *va, const void *vb) {
	const wait_record_t *const *pa = va;
	const wait_record_t *const *pb = vb;

	const wait_record_t *a = *pa;
	const wait_record_t *b = *pb;

	return (a->age < b->age) - (a->age > b->age); // higher ages should sort earlier
}

result_t waiter_wait(waiter_t *waiter, uint64_t timeout) {
	size_t num_records = 0;
	trn_mutex_lock(&waiter->mutex);
	for(wait_record_t *record = waiter->list.next; record != NULL; record = record->next) {
		if(num_records >= waiter->record_buffer_length) {
			size_t target_record_buffer_length = (num_records + 1) * 2;
			void *new_record_buffer = realloc(waiter->record_buffer, target_record_buffer_length * sizeof(*waiter->record_buffer));
			if(new_record_buffer == NULL) {
				trn_mutex_unlock(&waiter->mutex);
				return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			}
			waiter->record_buffer_length = target_record_buffer_length;
			waiter->record_buffer = new_record_buffer;
		}
		waiter->record_buffer[num_records] = record;
		num_records++;
	}

	qsort(waiter->record_buffer, num_records, sizeof(waiter->record_buffer[0]), record_compare);
	
	if(num_records > waiter->handle_buffer_length) {
		void *new_handle_buffer = realloc(waiter->handle_buffer, num_records * sizeof(*waiter->handle_buffer));
		if(new_handle_buffer == NULL) {
			trn_mutex_unlock(&waiter->mutex);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		waiter->handle_buffer_length = num_records;
		waiter->handle_buffer = new_handle_buffer;
	}

	for(size_t i = 0; i < num_records; i++) {
		waiter->handle_buffer[i] = waiter->record_buffer[i]->handle;
	}

	result_t r;
	uint32_t index;
	r = svcWaitSynchronization(&index, waiter->handle_buffer, num_records, timeout);
	if(r == RESULT_OK) {
		// touch handles that did not signal
		for(size_t i = 0; i <= index; i++) {
			waiter->record_buffer[i]->age = 0;
		}
		// increment age on handles that were not able to signal,
		// so they get sorted earlier next time and have a chance
		// to signal.
		for(size_t i = index+1; i < num_records; i++) {
			waiter->record_buffer[i]->age++;
		}

		wait_record_t *signalled_record = waiter->record_buffer[index];
		signalled_record->is_being_signalled = true;
		if(!signalled_record->signal(signalled_record->data, signalled_record->handle) || signalled_record->destroy_flag) {
			// if signal returns false, or wait_cancel deferred destruction, we unlink and free the record
			signalled_record->prev->next = signalled_record->next;
			if(signalled_record->next) {
				signalled_record->next->prev = signalled_record->prev;
			}
			free(signalled_record);
		} else {
			signalled_record->is_being_signalled = false;
		}
		trn_mutex_unlock(&waiter->mutex);
		return RESULT_OK;
	} else if(r == 0xea01) { // timeout
		// touch all records
		for(size_t i = 0; i < num_records; i++) {
			waiter->record_buffer[i]->age = 0;
		}
		trn_mutex_unlock(&waiter->mutex);
		return RESULT_OK;
	} else {
		trn_mutex_unlock(&waiter->mutex);
		return r;
	}
}

void waiter_cancel(waiter_t *waiter, wait_record_t *record) {
	trn_mutex_lock(&waiter->mutex);
	if(record->is_being_signalled) {
		// defer unlink+free until after signal handler exits
		record->destroy_flag = true;
	} else {
		record->prev->next = record->next;
		if(record->next) {
			record->next->prev = record->prev;
		}
		free(record);
	}
	trn_mutex_unlock(&waiter->mutex);
}

void waiter_destroy(waiter_t *waiter) {
	trn_mutex_lock(&waiter->mutex);
	for(wait_record_t *record = waiter->list.next; record != NULL;) {
		wait_record_t *next = record->next;
		free(record);
		record = next;
	}
	if(waiter->handle_buffer != NULL) {
		free(waiter->handle_buffer);
	}
	if(waiter->record_buffer != NULL) {
		free(waiter->record_buffer);
	}
	trn_mutex_unlock(&waiter->mutex);
	free(waiter);
}
