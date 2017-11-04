#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){
  printf("rand() generate integer in the range 0 to %d on this machine.\n", RAND_MAX);

  int i, n;
  n = 5;
  /* Set the random generator seed with epoch time. */
  srand((unsigned int)time(NULL));
  /* ran, rand_r, sran -- pseudo-random number generator, <stdlib.h>
  int rand(void);
  int rand_r(unsigned int *seedp);
  int srand(unsigned int seed);
  The rand() function returns a pseudo-random integer in the range
  0 to RAND_MAX inclusive.
  The srand() function sets its argument as the seed for a new sequence of
  pseudo-random integers to be returned by rand(). If no seed value is provided,
  the rand() function is automatically seeded with a value of 1.
  The rand() functio is not reentrant, you can use rand_r() function with the
  'seedp' argument to explicitly hold/keep the state of the function. */
  for (size_t i = 0; i < n; i++) {
    printf("%d\n", rand() % 50);
  }
  return 0;
}
