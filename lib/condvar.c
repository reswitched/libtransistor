#include<libtransistor/condvar.h>

#include<libtransistor/svc.h>
#include<libtransistor/tls.h>

void trn_condvar_create(trn_condvar_t *condvar) {
	condvar->key = 0;
}

result_t trn_condvar_signal(trn_condvar_t *condvar, int n) {
	return svcSignalProcessWideKey(&condvar->key, n);
}

result_t trn_condvar_wait(trn_condvar_t *condvar, trn_mutex_t *mutex, uint64_t timeout) NO_THREAD_SAFETY_ANALYSIS {
	result_t r;

	r = svcWaitProcessWideKeyAtomic((void*) &mutex->lock, &condvar->key, get_thread_handle(), timeout);

	if(r == 0xea01) {
		trn_mutex_lock(mutex);
	}

	return r;
}

void trn_condvar_destroy(trn_condvar_t *condvar) {
	condvar->key = -1;
}
