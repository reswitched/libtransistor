#include "phal.h"
#include "test.h"

const char * error_string;

int assertE;

///@todo: add cancellable wait for thread end for DSP/BIOS
///@todo: look at removing/changing ftime

static void runBarrierTests(void)
{
  printf("Barrier test #1\n");
  pthread_test_barrier1();

  printf("Barrier test #2\n");
  pthread_test_barrier2();

  printf("Barrier test #3\n");
  pthread_test_barrier3();

  printf("Barrier test #4\n");
  pthread_test_barrier4();

  printf("Barrier test #5\n");
  pthread_test_barrier5();
}

static void runSemTests(void)
{

  printf("Semaphore test #1\n");
  pthread_test_semaphore1();

  printf("Semaphore test #2\n");
  pthread_test_semaphore2();

  printf("Semaphore test #3\n");
  pthread_test_semaphore3();


  printf("Semaphore test #4\n");
  pthread_test_semaphore4();

  printf("Semaphore test #4t\n");
  pthread_test_semaphore4t();

  printf("Semaphore test #5\n");
  pthread_test_semaphore5();

  printf("Semaphore test #6\n");
  pthread_test_semaphore6();

}

static void runThreadTests(void)
{

  printf("Create test #1\n");
  pthread_test_create1();

  printf("Create test #2\n");
  pthread_test_create2();

  printf("Create test #3\n");
  pthread_test_create3();

  printf("Join test #0\n");
  pthread_test_join0();

  printf("Join test #1\n");
  pthread_test_join1();

  printf("Join test #2\n");
  pthread_test_join2();

  printf("Join test #3\n");
  pthread_test_join3();

  printf("Join test #4\n");
  printf("Depends on cancel. Not running.\n");
  //pthread_test_join4();

  printf("Kill test #1\n");
  printf("Depends on kill. Not running.\n");
  //pthread_test_kill1();

  printf("Exit test #1\n");
  pthread_test_exit1();

  printf("Exit test #2\n");
  pthread_test_exit2();

  printf("Exit test #3\n");
  pthread_test_exit3();

  printf("Exit test #4\n");
  printf("Cannot call pthread_exit() on a thread not created through pthread_create()");
  //pthread_test_exit4();

  printf("Exit test #5\n");
  printf("Cannot call pthread_exit() on a thread not created through pthread_create()");
  //pthread_test_exit5();

  /* These tests can not be run in series with other tests,
   * as they rely on knowing what is on the reuse queue.
   */
  /*
    printf("Reuse test #1\n");
    pthread_test_reuse1();

    printf("Reuse test #2\n");
    pthread_test_reuse2();
  */

//  printf("Priority test #1\n");
//  pthread_test_priority1();
//
//  printf("Priority test #2\n");
//  pthread_test_priority2();

//  printf("Inherit test #1\n");
//  pthread_test_inherit1();  ///@todo

}

static void runMiscTests(void)
{

  printf("Valid test #1\n");
  pthread_test_valid1();

  printf("Valid test #2\n");
  pthread_test_valid2();

  printf("Self test #1\n");
  pthread_test_self1();

  printf("Self test #2\n");
  pthread_test_self2();

  printf("Equal test #1\n");
  pthread_test_equal1();

  printf("Count test #1\n");
  pthread_test_count1();

  //printf("Delay test #1\n");
  //pthread_test_delay1();

  //printf("Delay test #2\n");
  //pthread_test_delay2();

  //printf("Once test #1\n");
  //pthread_test_once1();

  //printf("Once test #2\n");
  //pthread_test_once2();

  //printf("Once test #3\n");
  //pthread_test_once3();

  //printf("Once test #4\n");
  //pthread_test_once4();

  printf("TSD test #1\n");
  pthread_test_tsd1();

  printf("TSD test #2\n");
  pthread_test_tsd2();

#ifdef THREAD_SAFE_ERRNO
  printf("Errno test #1\n");
  pthread_test_errno1();
#endif // THREAD_SAFE_ERRNO

  printf("Detach test #1\n");
  pthread_test_detach1();

}

static void runMutexTests(void)
{

  printf("Mutex test #1\n");
  pthread_test_mutex1();

  printf("Mutex test #1(e)\n");
  pthread_test_mutex1e();

  printf("Mutex test #1(n)\n");
  pthread_test_mutex1n();

  printf("Mutex test #1(r)\n");
  pthread_test_mutex1e();

  printf("Mutex test #2\n");
  pthread_test_mutex2();

  printf("Mutex test #2(e)\n");
  pthread_test_mutex2e();

  printf("Mutex test #2(r)\n");
  pthread_test_mutex2r();

  printf("Mutex test #3\n");
  pthread_test_mutex3();

  printf("Mutex test #3(e)\n");
  pthread_test_mutex3e();

  printf("Mutex test #3(r)\n");
  pthread_test_mutex3r();

  printf("Mutex test #4\n");
  pthread_test_mutex4();

  printf("Mutex test #5\n");
  pthread_test_mutex5();

  printf("Mutex test #6\n");
  pthread_test_mutex6();

  printf("Mutex test #6e\n");
  pthread_test_mutex6e();

  printf("Mutex test #6es\n");
  pthread_test_mutex6es();

  printf("Mutex test #6n\n");
  pthread_test_mutex6n();

  printf("Mutex test #6r\n");
  pthread_test_mutex6r();

  printf("Mutex test #6rs\n");
  pthread_test_mutex6rs();

  printf("Mutex test #6s\n");
  pthread_test_mutex6s();

  printf("Mutex test #7\n");
  pthread_test_mutex7();

  printf("Mutex test #7e\n");
  pthread_test_mutex7e();

  printf("Mutex test #7n\n");
  pthread_test_mutex7n();

  printf("Mutex test #7r\n");
  pthread_test_mutex7r();

  //printf("Mutex test #8\n");
  //pthread_test_mutex8();

  //printf("Mutex test #8e\n");
  //pthread_test_mutex8e();

  //printf("Mutex test #8n\n");
  //pthread_test_mutex8n();

  //printf("Mutex test #8r\n");
  //pthread_test_mutex8r();

}

static void runSpinTests()
{
  printf("Spin test #1\n");
  pthread_test_spin1();

  printf("Spin test #2\n");
  pthread_test_spin2();

  printf("Spin test #3\n");
  pthread_test_spin3();

  //printf("Spin test #4\n");
  //pthread_test_spin4();

}

static void runCondvarTests()
{

  printf("Condvar test #1\n");
  pthread_test_condvar1();

  //printf("Condvar test #1-1\n");
  //pthread_test_condvar1_1();

  //printf("Condvar test #1-2\n");
  //pthread_test_condvar1_2();

  //printf("Condvar test #2\n");
  //pthread_test_condvar2();

  //printf("Condvar test #2-1\n");
  //pthread_test_condvar2_1();

  //printf("Condvar test #3\n");
  //pthread_test_condvar3();

  //printf("Condvar test #3-1\n");
  //pthread_test_condvar3_1();

  //printf("Condvar test #3-2\n");
  //pthread_test_condvar3_2();

  //printf("Condvar test #3-3\n");
  //pthread_test_condvar3_3();

  //printf("Condvar test #4\n");
  //pthread_test_condvar4();

  //printf("Condvar test #5\n");
  //pthread_test_condvar5();

  //printf("Condvar test #6\n");
  //pthread_test_condvar6();

  //printf("Condvar test #7\n");
  //pthread_test_condvar7();

  //printf("Condvar test #8\n");
  //pthread_test_condvar8();

  //printf("Condvar test #9\n");
  //pthread_test_condvar9();

}

static void runStressTests()
{
  //printf("Stress test #1\n");
  //pthread_test_stress1();
}

static void runRwlockTests()
{
  printf("Rwlock test #1\n");
  pthread_test_rwlock1();

  //printf("Rwlock test #2\n");
  //pthread_test_rwlock2();

  //printf("Rwlock test #2t\n");
  //pthread_test_rwlock2t();

  //printf("Rwlock test #3\n");
  //pthread_test_rwlock3();

  //printf("Rwlock test #3t\n");
  //pthread_test_rwlock3t();

  //printf("Rwlock test #4\n");
  //pthread_test_rwlock4();

  //printf("Rwlock test #4t\n");
  //pthread_test_rwlock4t();

  //printf("Rwlock test #5\n");
  //pthread_test_rwlock5();

  //printf("Rwlock test #5t\n");
  //pthread_test_rwlock5t();

  //printf("Rwlock test #6\n");
  //pthread_test_rwlock6();

  //printf("Rwlock test #6t\n");
  //pthread_test_rwlock6t();

  //printf("Rwlock test #6t2\n");
  //pthread_test_rwlock6t2();

  //printf("Rwlock test #7\n");
  //pthread_test_rwlock7();

  //printf("Rwlock test #8\n");
  //pthread_test_rwlock8();

}

static void runCancelTests()
{

  printf("Cancel test #1\n");
  pthread_test_cancel1();

  printf("Cancel test #2\n");
  pthread_test_cancel2();

  printf("Cancel test #3\n");
  pthread_test_cancel3();

  printf("Cancel test #4\n");
  pthread_test_cancel4();

  printf("Cancel test #5\n");
  pthread_test_cancel5();

  printf("Cancel test #6a\n");
  pthread_test_cancel6a();

  printf("Cancel test #6d\n");
  pthread_test_cancel6d();

  /* Cleanup only occurs for async cancellation.
   * If we don't support this, can't test it...
   */
  printf("Cleanup test #0\n");
  pthread_test_cleanup0();

  printf("Cleanup test #1\n");
  pthread_test_cleanup1();

  printf("Cleanup test #2\n");
  pthread_test_cleanup2();

  printf("Cleanup test #3\n");
  pthread_test_cleanup3();
}

static void runBenchTests()
{

  //printf("Benchmark test #1\n");
  //pthread_test_bench1();

  //printf("Benchmark test #2\n");
  //pthread_test_bench2();

  //printf("Benchmark test #3\n");
  //pthread_test_bench3();

  //printf("Benchmark test #4\n");
  //pthread_test_bench4();
}

static void runExceptionTests()
{
  //printf("Exception test #1\n");
  //pthread_test_exception1();

/*// This test intentially crashes the app
  // (unhandled exception)
  //printf("Exception test #2\n");
  //pthread_test_exception2();
*///

  //printf("Exception test #3\n");
  //pthread_test_exception3();
}

void pte_test_main()
{
  int i;

  // Dynamically initialize.
  /*if (!pthread_init())
    {
      printf("Failed to initialize pthreads library.\n");
      return;
    }*/

  printf("Running tests...\n");
  for (i=0;i<2;i++)
    {
      printf("=========================\n");
      printf("   Test iteration #%d\n\n",i);
      printf("=========================\n");

      runThreadTests(); 
      runMiscTests();
      //runMutexTests();
      //runSemTests();
      //runCondvarTests();
      //runBarrierTests();
      //runSpinTests();
      //runRwlockTests();
      //runCancelTests();
      //runExceptionTests();
      //runBenchTests();
      //runStressTests();

    }

  printf("Tests complete!\n");

}

