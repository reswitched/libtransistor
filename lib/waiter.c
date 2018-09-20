#include<libtransistor/waiter.h>

#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/mutex.h>

#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
	WAIT_RECORD_TYPE_EVENT,
	WAIT_RECORD_TYPE_DEADLINE,
	WAIT_RECORD_TYPE_SIGNAL,
} wait_record_type_t;

struct wait_record_t {
	void *data;
	wait_record_t *prev;
	wait_record_t *next;
	bool is_running_callback;
	bool is_linked;
	bool is_externally_referenced;
	bool destroy_flag;
	wait_record_type_t type;
	union {
		struct {
			bool (*callback)(void *data, handle_t handle);
			handle_t handle;
			uint64_t age;
		} event;
		struct {
			uint64_t (*callback)(void *data);
			uint64_t deadline;
		} deadline;
		struct {
			bool (*callback)(void *data);
			bool is_signalled;
		} signal;
	};
};

struct waiter_t {
	trn_recursive_mutex_t mutex;
	wait_record_t list;
	
	size_t handle_buffer_length;
	handle_t *handle_buffer;

	size_t event_record_buffer_length;
	wait_record_t **event_record_buffer;
};

waiter_t *waiter_create() {
	waiter_t *waiter = malloc(sizeof(*waiter));
	if(waiter == NULL) {
		return NULL;
	}
	
	memset(waiter, 0, sizeof(*waiter));
	trn_recursive_mutex_create(&waiter->mutex);
	return waiter;
}

wait_record_t *waiter_add(waiter_t *waiter, handle_t handle, bool (*callback)(void *data, handle_t handle), void *data) {
	wait_record_t *record = malloc(sizeof(*record));
	if(record == NULL) {
		return NULL;
	}

	memset(record, 0, sizeof(*record));
	record->data = data;
	record->is_externally_referenced = true;
	record->type = WAIT_RECORD_TYPE_EVENT;
	record->event.callback = callback;
	record->event.handle = handle;
	record->event.age = 0;

	trn_recursive_mutex_interrupt_lock(&waiter->mutex);
	record->prev = &waiter->list;
	record->next = waiter->list.next;
	if(record->next) {
		record->next->prev = record;
	}
	waiter->list.next = record;
	record->is_linked = true;
	trn_recursive_mutex_unlock(&waiter->mutex);

	return record;
}

wait_record_t *waiter_add_deadline(waiter_t *waiter, uint64_t deadline, uint64_t (*callback)(void *data), void *data) {
	wait_record_t *record = malloc(sizeof(*record));
	if(record == NULL) {
		return NULL;
	}

	memset(record, 0, sizeof(*record));
	record->data = data;
	record->is_externally_referenced = true;
	record->type = WAIT_RECORD_TYPE_DEADLINE;
	record->deadline.callback = callback;
	record->deadline.deadline = deadline;

	trn_recursive_mutex_interrupt_lock(&waiter->mutex);
	record->prev = &waiter->list;
	record->next = waiter->list.next;
	if(record->next) {
		record->next->prev = record;
	}
	waiter->list.next = record;
	record->is_linked = true;
	trn_recursive_mutex_unlock(&waiter->mutex);

	return record;
}

wait_record_t *waiter_add_signal(waiter_t *waiter, bool (*callback)(void *data), void *data) {
	wait_record_t *record = malloc(sizeof(*record));
	if(record == NULL) {
		return NULL;
	}

	memset(record, 0, sizeof(*record));
	record->data = data;
	record->is_externally_referenced = true;
	record->type = WAIT_RECORD_TYPE_SIGNAL;
	record->signal.callback = callback;

	trn_recursive_mutex_interrupt_lock(&waiter->mutex);
	record->prev = &waiter->list;
	record->next = waiter->list.next;
	if(record->next) {
		record->next->prev = record;
	}
	waiter->list.next = record;
	record->is_linked = true;
	trn_recursive_mutex_unlock(&waiter->mutex);

	return record;
}

void waiter_signal(waiter_t *waiter, wait_record_t *record) {
	if(record->type == WAIT_RECORD_TYPE_SIGNAL) {
		trn_recursive_mutex_interrupt_lock(&waiter->mutex);
		record->signal.is_signalled = true;
		trn_recursive_mutex_unlock(&waiter->mutex);
	}
}

void waiter_reset_signal(waiter_t *waiter, wait_record_t *record) {
	record->signal.is_signalled = false;
}

static void record_unregister(wait_record_t *record) {
	if(record->is_linked) {
		record->prev->next = record->next;
		if(record->next) {
			record->next->prev = record->prev;
		}
		record->is_linked = false;
	}
	// don't free things that user might have a pointer to
	if(!record->is_externally_referenced) {
		free(record);
	}
}

static int event_record_compare(const void *va, const void *vb) {
	const wait_record_t *const *pa = va;
	const wait_record_t *const *pb = vb;

	const wait_record_t *a = *pa;
	const wait_record_t *b = *pb;

	return (a->event.age < b->event.age) - (a->event.age > b->event.age); // higher ages should sort earlier
}

result_t waiter_wait(waiter_t *waiter, uint64_t timeout) {
	uint64_t now = svcGetSystemTick();
	uint64_t next_deadline = 0;
	size_t num_event_records = 0;
	trn_recursive_mutex_lock(&waiter->mutex);
	for(wait_record_t *record = waiter->list.next; record != NULL; record = record->next) {
		if(record->type == WAIT_RECORD_TYPE_EVENT) {
			// reallocate event record buffer if it's too small
			if(num_event_records >= waiter->event_record_buffer_length) {
				size_t target_event_record_buffer_length = (num_event_records + 1) * 2;
				void *new_event_record_buffer = realloc(waiter->event_record_buffer, target_event_record_buffer_length * sizeof(*waiter->event_record_buffer));
				if(new_event_record_buffer == NULL) {
					trn_recursive_mutex_unlock(&waiter->mutex);
					return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				}
				waiter->event_record_buffer_length = target_event_record_buffer_length;
				waiter->event_record_buffer = new_event_record_buffer;
			}
			// add this event to the event record buffer
			waiter->event_record_buffer[num_event_records] = record;
			num_event_records++;
		} else if(record->type == WAIT_RECORD_TYPE_DEADLINE) {
			// signal expired deadlines.
			// this is a while loop in case the callback updates the deadline to another expired value
			while(record->deadline.deadline <= now) {
				record->is_running_callback = true;
				record->deadline.deadline = record->deadline.callback(record->data);
				record->is_running_callback = false;
				
				if(record->deadline.deadline == 0 || record->destroy_flag) {
					wait_record_t *prev_record = record->prev;
					record_unregister(record);
					record = prev_record; // so we can keep iterating
					goto prepare_next_record; // muahaha
				}
			}
			// keep track of the closest deadline
			if(next_deadline == 0 || record->deadline.deadline < next_deadline) {
				next_deadline = record->deadline.deadline;
			}
		} else if(record->type == WAIT_RECORD_TYPE_SIGNAL) {
			if(record->signal.is_signalled) {
				record->is_running_callback = true;
				bool r = record->signal.callback(record->data);
				record->is_running_callback = false;

				if(!r || record->destroy_flag) {
					wait_record_t *prev_record = record->prev;
					record_unregister(record);
					record = prev_record; // so we can keep iterating
					goto prepare_next_record; // muahaha
				}
			}
		}
	prepare_next_record:;
	}

	// sort events by how long ago we knew whether they were signalled or not,
	// so the kernel will inform us of their status instead of letting the
	// events that were registered first dominate.
	qsort(waiter->event_record_buffer, num_event_records, sizeof(waiter->event_record_buffer[0]), event_record_compare);

	// reallocate handle buffer if it's too small
	if(num_event_records > waiter->handle_buffer_length) {
		void *new_handle_buffer = realloc(waiter->handle_buffer, num_event_records * sizeof(*waiter->handle_buffer));
		if(new_handle_buffer == NULL) {
			trn_recursive_mutex_unlock(&waiter->mutex);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		waiter->handle_buffer_length = num_event_records;
		waiter->handle_buffer = new_handle_buffer;
	}

	// copy event record handles to handle buffer
	for(size_t i = 0; i < num_event_records; i++) {
		waiter->handle_buffer[i] = waiter->event_record_buffer[i]->event.handle;
	}

	// calculate our maximum timeout based on the next deadline
	uint64_t ticks_until_deadline = next_deadline - svcGetSystemTick();
	uint64_t deadline_timeout = ticks_until_deadline * 10000 / 192; // convert ticks to nanoseconds
	if(deadline_timeout < timeout) {
		timeout = deadline_timeout;
	}
	
	result_t r;
	uint32_t index;
	r = svcWaitSynchronization(&index, waiter->handle_buffer, num_event_records, timeout);
	if(r == RESULT_OK) {
		// touch handles that did not signal
		for(size_t i = 0; i <= index; i++) {
			waiter->event_record_buffer[i]->event.age = 0;
		}
		// increment age on handles that were not able to signal,
		// so they get sorted earlier next time and have a chance
		// to signal.
		for(size_t i = index+1; i < num_event_records; i++) {
			waiter->event_record_buffer[i]->event.age++;
		}

		wait_record_t *signalled_record = waiter->event_record_buffer[index];
		signalled_record->is_running_callback = true;
		bool r = signalled_record->event.callback(signalled_record->data, signalled_record->event.handle);
		signalled_record->is_running_callback = false;
		if(r || signalled_record->destroy_flag) { // destroy_flag is set when callback calls waiter_cancel
			record_unregister(signalled_record);
		}
		trn_recursive_mutex_unlock(&waiter->mutex);
		return RESULT_OK;
	} else if(r == 0xea01 || r == 0xec01) { // timeout or interrupt
		// touch all records
		for(size_t i = 0; i < num_event_records; i++) {
			waiter->event_record_buffer[i]->event.age = 0;
		}
		trn_recursive_mutex_unlock(&waiter->mutex);
		return RESULT_OK;
	} else {
		trn_recursive_mutex_unlock(&waiter->mutex);
		return r;
	}
}

void waiter_cancel(waiter_t *waiter, wait_record_t *record) {
	trn_recursive_mutex_interrupt_lock(&waiter->mutex);
	record->is_externally_referenced = false; // user is no longer interested in keeping this alive
	if(record->is_running_callback) {
		// defer unlink+free until after callback exits
		record->destroy_flag = true;
	} else {
		if(record->is_linked) {
			record->prev->next = record->next;
			if(record->next) {
				record->next->prev = record->prev;
			}
		}
		free(record);
	}
	trn_recursive_mutex_unlock(&waiter->mutex);
}

void waiter_destroy(waiter_t *waiter) {
	trn_recursive_mutex_interrupt_lock(&waiter->mutex);
	for(wait_record_t *record = waiter->list.next; record != NULL;) {
		wait_record_t *next = record->next;
		free(record);
		record = next;
	}
	if(waiter->handle_buffer != NULL) {
		free(waiter->handle_buffer);
	}
	if(waiter->event_record_buffer != NULL) {
		free(waiter->event_record_buffer);
	}
	trn_recursive_mutex_unlock(&waiter->mutex);
	free(waiter);
}
