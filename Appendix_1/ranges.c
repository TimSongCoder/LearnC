#include <stdio.h>
#include <limits.h>

/* The <limits.h> hearder shall define macros and symbolic constants for various
limits. Different categories of limits representing various limits on resources
that the implementation imposes on applications. Such as range limits on integer
data type, operating system and file system limits, etc.

You can use fpathconf(), pathconf() and sysconf() functions defined in 'unistd.h'
to determine configurable pathname variables on different OS in addition. For
system configuration... */
int main(){
  printf("On this machine:\nAn int takes up %lu bytes\n", sizeof(int));
  printf("And ints can store values from %i to %i\n", INT_MIN, INT_MAX);

  printf("A short takes up %lu bytes\n", sizeof(short));
  printf("And shorts can store values from %i to %i\n", SHRT_MIN, SHRT_MAX);
  return 0;
}
