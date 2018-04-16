/**
 * @file libtransistor/mutex.h
 * @brief Mutex functions and thread-safety macros
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<stdatomic.h>

#define THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))

#define CAPABILITY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(capability(x))

#define SCOPED_CAPABILITY	  \
	THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)

#define GUARDED_BY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))

#define PT_GUARDED_BY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))

#define ACQUIRED_BEFORE(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))

#define ACQUIRED_AFTER(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))

#define REQUIRES(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(requires_capability(__VA_ARGS__))

#define REQUIRES_SHARED(...)	  \
	THREAD_ANNOTATION_ATTRIBUTE__(requires_shared_capability(__VA_ARGS__))

#define ACQUIRE(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

#define ACQUIRE_SHARED(...)	  \
	THREAD_ANNOTATION_ATTRIBUTE__(acquire_shared_capability(__VA_ARGS__))

#define RELEASE(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define RELEASE_SHARED(...)	  \
	THREAD_ANNOTATION_ATTRIBUTE__(release_shared_capability(__VA_ARGS__))

#define TRY_ACQUIRE(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_capability(__VA_ARGS__))

#define TRY_ACQUIRE_SHARED(...)	  \
	THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_shared_capability(__VA_ARGS__))
	
#define EXCLUDES(...)	\
	THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

#define ASSERT_CAPABILITY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(assert_capability(x))

#define ASSERT_SHARED_CAPABILITY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_capability(x))

#define RETURN_CAPABILITY(x)	\
	THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))

#define NO_THREAD_SAFETY_ANALYSIS	\
	THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)

typedef struct CAPABILITY("mutex") {
	volatile atomic_uint_fast64_t lock;
} trn_mutex_t;

#define TRN_MUTEX_STATIC_INITIALIZER {.lock = 0}

typedef struct CAPABILITY("recursive mutex") {
	trn_mutex_t mutex;
	thread_h owner;
	int count;
} trn_recursive_mutex_t;

#define TRN_RECURSIVE_MUTEX_STATIC_INITIALIZER {.mutex = TRN_MUTEX_STATIC_INITIALIZER, .owner = 0, .count = 0}

void trn_mutex_create(trn_mutex_t *mutex);
void trn_mutex_lock(trn_mutex_t *mutex) ACQUIRE(mutex);
bool trn_mutex_try_lock(trn_mutex_t *mutex) TRY_ACQUIRE(true, mutex); // true on success
void trn_mutex_unlock(trn_mutex_t *mutex) RELEASE(mutex);
void trn_recursive_mutex_create(trn_recursive_mutex_t *recursive);
void trn_recursive_mutex_lock(trn_recursive_mutex_t *recursive) ACQUIRE(recursive);
bool trn_recursive_mutex_try_lock(trn_recursive_mutex_t *recursive) TRY_ACQUIRE(true, recursive); // true on success
void trn_recursive_mutex_unlock(trn_recursive_mutex_t *recursive) RELEASE(recursive);

#ifdef __cplusplus
}
#endif
