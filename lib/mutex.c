#include<libtransistor/mutex.h>

#include<libtransistor/types.h>
#include<libtransistor/tls.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>

#include<stdatomic.h>

#define HAS_LISTENERS ((uint64_t) 1 << 32)

void trn_mutex_create(trn_mutex_t *mutex) {
	mutex->lock = 0;
}

void trn_mutex_lock(trn_mutex_t *mutex) ACQUIRE(mutex) NO_THREAD_SAFETY_ANALYSIS {
	thread_h self_handle = get_thread_handle();
	while(1) {
		uint64_t cur = 0;
		if(atomic_compare_exchange_strong(&mutex->lock, &cur, self_handle)) { // uncontended
			return;
		}
		
		if((cur & ~HAS_LISTENERS) == self_handle) { // we own it
			return;
		}

		if(!(cur & HAS_LISTENERS)) {
			// flag it so that the unlock gets arbitrated
			if(!atomic_compare_exchange_strong(&mutex->lock, &cur, cur | HAS_LISTENERS)) {
				continue; // handles the case where it was unlocked right after we checked HAS_LISTENERS
			}
		}

		svcArbitrateLock(cur & ~HAS_LISTENERS, (void*) &mutex->lock, self_handle);
	}
}

void trn_mutex_interrupt_lock(trn_mutex_t *mutex) ACQUIRE(mutex) NO_THREAD_SAFETY_ANALYSIS {
	thread_h self_handle = get_thread_handle();
	while(1) {
		uint64_t cur = 0;
		if(atomic_compare_exchange_strong(&mutex->lock, &cur, self_handle)) { // uncontended
			return;
		}
		
		if((cur & ~HAS_LISTENERS) == self_handle) { // we own it
			return;
		}

		if(!(cur & HAS_LISTENERS)) {
			// flag it so that the unlock gets arbitrated
			if(!atomic_compare_exchange_strong(&mutex->lock, &cur, cur | HAS_LISTENERS)) {
				continue; // handles the case where it was unlocked right after we checked HAS_LISTENERS
			}
		}

		svcCancelSynchronization(cur & ~HAS_LISTENERS); // interrupt the thread that holds the mutex
		svcArbitrateLock(cur & ~HAS_LISTENERS, (void*) &mutex->lock, self_handle);
	}
}

bool trn_mutex_try_lock(trn_mutex_t *mutex) TRY_ACQUIRE(true, mutex) NO_THREAD_SAFETY_ANALYSIS {
	uint64_t cur = 0;
	thread_h self_handle = get_thread_handle();
	if(atomic_compare_exchange_strong(&mutex->lock, &cur, self_handle)) {
		return true;
	}

	if((cur & ~HAS_LISTENERS) == self_handle) { // we already own it
		return true;
	}

	return false;
}

void trn_mutex_unlock(trn_mutex_t *mutex) RELEASE(mutex) NO_THREAD_SAFETY_ANALYSIS {
	uint64_t old = atomic_exchange(&mutex->lock, 0);
	if(old & HAS_LISTENERS) {
		svcArbitrateUnlock((void*) &mutex->lock);
	}
}

void trn_recursive_mutex_create(trn_recursive_mutex_t *recursive) {
	trn_mutex_create(&recursive->mutex);
	recursive->owner = 0;
	recursive->count = 0;
}

void trn_recursive_mutex_lock(trn_recursive_mutex_t *recursive) ACQUIRE(recursive) NO_THREAD_SAFETY_ANALYSIS {
	thread_h self_handle = get_thread_handle();
	if(recursive->owner != self_handle) {
		trn_mutex_lock(&recursive->mutex);
		recursive->owner = self_handle;
	}
	recursive->count++;
}

void trn_recursive_mutex_interrupt_lock(trn_recursive_mutex_t *recursive) ACQUIRE(recursive) NO_THREAD_SAFETY_ANALYSIS {
	thread_h self_handle = get_thread_handle();
	if(recursive->owner != self_handle) {
		trn_mutex_interrupt_lock(&recursive->mutex);
		recursive->owner = self_handle;
	}
	recursive->count++;
}

bool trn_recursive_mutex_try_lock(trn_recursive_mutex_t *recursive) TRY_ACQUIRE(true, recursive) NO_THREAD_SAFETY_ANALYSIS {
	thread_h self_handle = get_thread_handle();
	if(recursive->owner != self_handle) {
		if(!trn_mutex_try_lock(&recursive->mutex)) {
			return false;
		}
		recursive->owner = self_handle;
	}
	recursive->count++;
	return true;
}

void trn_recursive_mutex_unlock(trn_recursive_mutex_t *recursive) RELEASE(recursive) NO_THREAD_SAFETY_ANALYSIS {
	if(--(recursive->count) == 0) {
		recursive->owner = 0;
		trn_mutex_unlock(&recursive->mutex);
	}
}
