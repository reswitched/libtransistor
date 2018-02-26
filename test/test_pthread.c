#include <pthread.h>

// Test threads
void test_thread() {
	pthread_attr_t attr;
	pthread_t thread;

	pthread_attr_init(&attr);
	pthread_create(&thread, &attr, NULL, NULL);
}

// Test mutexes
void test_mutex() {
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&mutex, &attr);
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_trylock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

int main() {
	test_thread();
	test_mutex();

	return 0;
}
