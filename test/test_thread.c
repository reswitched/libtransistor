#include<libtransistor/util.h>
#include<libtransistor/thread.h>
#include<libtransistor/svc.h>

#include<stdio.h>

void other_thread(void *arg) {
	printf("other thread started: %p\n", arg);
}

int main(int argc, char *argv[]) {
	result_t r;

	trn_thread_t thread;
	ASSERT_OK(fail, trn_thread_create(&thread, other_thread, NULL, 0x3f, -2, 1024 * 64, NULL));
	ASSERT_OK(fail_thread, trn_thread_start(&thread));
	ASSERT_OK(fail_thread, trn_thread_join(&thread, -1));
	printf("thread exited\n");
	
fail_thread:
	trn_thread_destroy(&thread);
fail:
	return r;
}
