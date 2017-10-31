#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> /* POSIX thread library header file. */

void error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

/* Thread functions need to have a void* return type. */
void* does_not(void *a){
  int i = 0;
  for( i = 0; i < 5; i++){
    sleep(1);
    puts("Does not!");
  }
  return NULL;
}

void* does_too(void *a){
  int i = 0;
  for(i = 0; i < 5; i++){
    sleep(1);
    puts("Does too!");
  }
  return NULL;
}

int main(){
  pthread_t t0, t1;
  /* pthread_create -- create a new thread. <pthread.h>
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg);
  The pthread_create() function starts a new thread in the calling
  process. The new thread starts execution by invoking start_routine() funciton;
  'arg' is passed as the sole argument of start_routine().
  The new threads terminates in one of the following ways:
    1. It calls pthread_exit(), specifying an exit status value that is available
    to another thread in the same process that calls pthread_join().
    2. It returns from start_routine(). This is equivalent to calling pthread_exit()
    with the value supplied in the return statement.
    3. It is canceled (pthread_cancel()).
    4. Any of the threads in the process calls exit(), or the main thread performs
    a return from main(). This causes the termination of all threads in the process.

  On success, pthread_create() returns 0; on error, it returns an error number. */
  if(pthread_create(&t0, NULL, does_not, NULL) != 0){
    error("Can't create thread t0");
  }
  if(pthread_create(&t1, NULL, does_too, NULL) != 0 ){
    error("Can't create thread t1");
  }

  void *result;
  /* pthread_join -- join with a terminated thread.
  int pthread_join(pthread_t thread, void **retval);

  The pthread_join() function waits for the thread specified by 'thread' to
  terminate. If that thread has already terminated, then pthread_join() returns
  immediately. The thread specified by 'thread' must be joinable.
  If retval is not NULL, then pthread_join() copies the exit status of the target
  thread into the location pointed by *retval. If the target thread was canceled,
  then PTHREAD_CANCELED is placed in *retval.
  If multiple threads simultaneously try to join with the same thread, the results
  are undefined. If the thread calling pthread_join() is canceled, then the target
  thread will remain joinable.
  On success, pthread_join() returns 0; on error, it returns an error number. */
  if(pthread_join(t0, &result) != 0){
    error("Can't join thread t0");
  }
  if(pthread_join(t1, &result) != 0){
    error("Can't join thread t1");
  }

  return 0;
}
