#include <stdio.h>
#include <pthread.h>

void* do_stuff(void *param){
  long thread_no = (long)param; /* long data type is guaranteed not smaller than pointer. */
  printf("Thread number %ld\n", thread_no);
  return (void *)(thread_no + 1);
}

int main(){
  pthread_t threads[30];
  long t;
  for (t=0; t < 30; t++){
    pthread_create(&threads[t], NULL, do_stuff, (void *)t);
  }
  void* result;
  for (t = 0; t < 30; t++){
    pthread_join(threads[t], &result);
    printf("Thread %ld returned %ld\n", t, (long)result); /* Convert the return value to a long. */
  }
  return 0;
}
