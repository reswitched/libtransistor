#include<libtransistor/util.h>
#include<libtransistor/mutex.h>
#include<libtransistor/condvar.h>
#include<libtransistor/thread.h>
#include<libtransistor/svc.h>

#include<stdio.h>

static trn_mutex_t mutex;
static trn_condvar_t condvar;
static volatile bool pred = 0;

void other_thread(void *arg) {
	printf("O: other thread started\n");

	printf("O: trying to lock mutex\n");
	trn_mutex_lock(&mutex);
	printf("O: acquired mutex\n");
	while(!pred) {
		printf("O: waiting on condvar...\n");
		trn_condvar_wait(&condvar, &mutex, -1);
		printf("O: woke up\n");
	}
	trn_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
	result_t r;
	trn_mutex_create(&mutex);
	trn_condvar_create(&condvar);

	trn_thread_t thread;
	ASSERT_OK(fail, trn_thread_create(&thread, other_thread, NULL, -1, -2, 1024 * 64, NULL));
	ASSERT_OK(fail_thread, trn_thread_start(&thread));

	printf("M: started other thread\n");
	svcSleepThread(5000000000);
	printf("M: signalling spuriously\n");
	trn_condvar_signal(&condvar, 1);
	svcSleepThread(5000000000);
	printf("M: signalling\n");
	pred = 1;
	trn_condvar_signal(&condvar, 1);

	trn_thread_join(&thread, -1);

fail_thread:
	trn_thread_destroy(&thread);
fail:
	return r;
}
