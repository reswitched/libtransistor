#include<libtransistor/util.h>
#include<libtransistor/mutex.h>
#include<libtransistor/thread.h>
#include<libtransistor/svc.h>

#include<stdio.h>

static trn_mutex_t mutex;

void other_thread(void *arg) {
	printf("O: other thread started: %p\n", arg);
	bool t;
	printf("O: trying to lock mutex: %d\n", (int) (t = trn_mutex_try_lock(&mutex)));
	if(t) {
		printf("O: invalid state\n");
		trn_mutex_unlock(&mutex);
		return;
	}
	printf("O: locking mutex...\n");
	trn_mutex_lock(&mutex);
	printf("O: locked mutex!\n");
	trn_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
	result_t r;
	trn_mutex_create(&mutex);

	trn_thread_t thread;
	ASSERT_OK(fail, trn_thread_create(&thread, other_thread, NULL, 0x3f, -2, 1024 * 64, NULL));
	trn_mutex_lock(&mutex);
	ASSERT_OK(fail_mutex, trn_thread_start(&thread));
	printf("M: started other thread\n");
	svcSleepThread(5000000000);
	printf("M: unlocking mutex\n");
	trn_mutex_unlock(&mutex);
	printf("M: unlocked mutex, yielding...\n");
	svcSleepThread(0);
	printf("M: returned execution, joining thread...\n");
	ASSERT_OK(fail_thread, trn_thread_join(&thread, -1));
	printf("thread exited\n");
	
	trn_thread_destroy(&thread);
	return RESULT_OK;
	
fail_mutex:
	trn_mutex_unlock(&mutex);
fail_thread:
	trn_thread_destroy(&thread);
fail:
	return r;
}
