#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int beers = 2000000;

/* PTHREAD_MUTEX_INITIALIZER macro initializes a static mutex, setting its attributes
to default values, no error checking is performed. Defined in pthread.h header file. */
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void * drink_lots(void *a){
  int i;
  /* pthread_mutex_lock -- lock a mutex. <pthread.h>
  int pthread_mutex_lock(pthread_mutex_t *mutex);

  The pthread_mutex_lock() function locks 'mutex'. If the mutex is already locked,
  the calling thread will block until the mutex becomes available.
  If successful, the pthread_mutex_lock() function will return zero, otherwise
  an error number will be returned to indicate the error. */
  pthread_mutex_lock(&beers_lock);
  for (i = 0; i < 100000; i++){
   beers = beers - 1;
  }
  /* pthread_mutex_unlock -- unlock a mutex. <pthread.h>
  int pthread_mutex_unlock(pthread_mutex_t *mutex);

  If the current thread holds the lock on 'mutex', then the pthread_mutex_unlock()
  function unlocks 'mutex'. Calling pthread_mutex_unlock() with a 'mutex' that
  the calling thread does not hold will result in undefined behavior.
  If successful, pthread_mutex_unlock() function will return zero, otherwise an error
  number will be returned to indicate the error.
   */
  pthread_mutex_unlock(&beers_lock);
  printf("beers = %i\n", beers);
  return NULL;
}

void error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main(){
  pthread_t threads[20];
  int i;
  printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);
  for (i=0; i < 20; i++){
    if(pthread_create(&threads[i], NULL, drink_lots, NULL) != 0){
      error("Can't create thread.");
    }
  }
  /* As per to the design, the main thread needs to wait the other newly created
  counting threads. */
  void* result;
  for (i = 0; i < 20; i++){
    /* pthread_join -- wait for thread termination. <pthread.h>
    int pthread_join(pthread_t thread, void **value_ptr);

    The pthread_join() function SUSPENDS execution of the calling thread until the
    until the target 'thread' terminates unless the target 'thread' has already
    terminated. */
    if(pthread_join(threads[i], &result) != 0){
      error("Can't join thread.");
    }
  }
  printf("There are now %i bottles of beer on the wall\n", beers);
  return 0;
}
