#include<libtransistor/tls.h>

thread_h get_thread_handle() {
	return get_tls()->thread->handle;
}

trn_thread_t *trn_get_thread() {
	return get_tls()->thread;
}
