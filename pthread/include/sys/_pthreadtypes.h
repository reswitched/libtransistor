#pragma once

/*
 * Forward structure definitions.
 *
 * These are mostly opaque to the user.
 */
struct pthread;
struct pthread_attr;
struct pthread_cond;
struct pthread_cond_attr;
struct pthread_mutex;
struct pthread_mutex_attr;
struct pthread_once;
struct pthread_rwlock;
struct pthread_rwlockattr;

/*
 * Primitive system data type definitions required by P1003.1c.
 *
 * Note that P1003.1c specifies that there are no defined comparison
 * or assignment operators for the types pthread_attr_t, pthread_cond_t,
 * pthread_condattr_t, pthread_mutex_t, pthread_mutexattr_t.
 */
typedef struct	pthread			*pthread_t;
typedef struct	pthread_attr		*pthread_attr_t;
typedef volatile struct pthread_mutex	*pthread_mutex_t;
typedef struct	pthread_mutex_attr	*pthread_mutexattr_t;
typedef struct	pthread_cond		*pthread_cond_t;
typedef struct	pthread_cond_attr	*pthread_condattr_t;
typedef int				pthread_key_t;
typedef struct	pthread_once		pthread_once_t;
typedef struct	pthread_rwlock		*pthread_rwlock_t;
typedef struct	pthread_rwlockattr	*pthread_rwlockattr_t;
typedef struct	pthread_barrier		*pthread_barrier_t;
typedef struct	pthread_barrierattr	*pthread_barrierattr_t;
typedef struct	pthread_spinlock	*pthread_spinlock_t;
