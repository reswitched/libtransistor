/*
 * rwlock8.c
 *
 * Hammer on a bunch of rwlocks to test robustness and fairness.
 * Printed stats should be roughly even for each thread.
 *
 * Yield during each access to exercise lock contention code paths
 * more than rwlock7.c does (particularly on uni-processor systems).
 */

#include "test.h"

#ifdef __GNUC__
#include <stdlib.h>
#endif

#define THREADS         5
#define DATASIZE        7
#define ITERATIONS      10000

/*
 * Keep statistics for each thread.
 */
typedef struct thread_tag
  {
    int         thread_num;
    pthread_t   thread_id;
    int         updates;
    int         reads;
    int         changed;
    unsigned int         seed;
  } thread_t;

/*
 * Read-write lock and shared data
 */
typedef struct data_tag
  {
    pthread_rwlock_t    lock;
    int                 data;
    int                 updates;
  } data_t;

static thread_t threads[THREADS];
static data_t data[DATASIZE];

/*
 * Thread start routine that uses read-write locks
 */
static void *thread_routine (void *arg)
{
  thread_t *self = (thread_t*)arg;
  int iteration;
  int element = 0;
  int interval = 1 + rand() % 71;

  self->changed = 0;

  for (iteration = 0; iteration < ITERATIONS; iteration++)
    {
      /*
            if (iteration % (ITERATIONS / 10) == 0)
              {
                putchar('.');
                fflush(stdout);
              }
      */
      /*
       * Each "self->interval" iterations, perform an
       * update operation (write lock instead of read
       * lock).
       */
      if ((iteration % interval) == 0)
        {
          assert(pthread_rwlock_wrlock (&data[element].lock) == 0);
          data[element].data = self->thread_num;
          data[element].updates++;
          self->updates++;
          interval = 1 + rand() % 71;
          sched_yield();
          assert(pthread_rwlock_unlock (&data[element].lock) == 0);
        }
      else
        {
          /*
           * Look at the current data element to see whether
           * the current thread last updated it. Count the
           * times, to report later.
           */
          assert(pthread_rwlock_rdlock (&data[element].lock) == 0);

          self->reads++;

          if (data[element].data != self->thread_num)
            {
              self->changed++;
              interval = 1 + self->changed % 71;
            }

          sched_yield();

          assert(pthread_rwlock_unlock (&data[element].lock) == 0);
        }

      element = (element + 1) % DATASIZE;

    }

  return NULL;
}

int pthread_test_rwlock8()
{
  int count;
  int data_count;
  int thread_updates = 0;
  int data_updates = 0;

  struct _timeb currSysTime1;
  struct _timeb currSysTime2;

  /*
   * Initialize the shared data.
   */
  for (data_count = 0; data_count < DATASIZE; data_count++)
    {
      data[data_count].data = 0;
      data[data_count].updates = 0;

      assert(pthread_rwlock_init (&data[data_count].lock, NULL) == 0);
    }

  _ftime(&currSysTime1);

  /*
   * Create THREADS threads to access shared data.
   */
  for (count = 0; count < THREADS; count++)
    {
      threads[count].thread_num = count;
      threads[count].updates = 0;
      threads[count].reads = 0;
      threads[count].seed = 1 + rand() % 71;

      assert(pthread_create (&threads[count].thread_id,
                             NULL, thread_routine, (void*)&threads[count]) == 0);
    }

  /*
   * Wait for all threads to complete, and collect
   * statistics.
   */
  for (count = 0; count < THREADS; count++)
    {
      assert(pthread_join (threads[count].thread_id, NULL) == 0);
    }
  for (count = 0; count < THREADS; count++)
    {
      thread_updates += threads[count].updates;
    }
  /*
    putchar('\n');
    fflush(stdout);
  */

  /*
   * Collect statistics for the data.
   */
  for (data_count = 0; data_count < DATASIZE; data_count++)
    {
      data_updates += data[data_count].updates;
      assert(pthread_rwlock_destroy (&data[data_count].lock) == 0);
    }

  _ftime(&currSysTime2);

  return 0;
}
