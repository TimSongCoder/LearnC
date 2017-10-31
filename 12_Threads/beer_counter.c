#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int beers = 2000000;

void * drink_lots(void *a){
  int i;
  for (i = 0; i < 100000; i++){
   beers = beers - 1;
  }
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
