#include <stdio.h>

int counter(){
  /* The 'static' keyword will store the variable inside the global area of memory,
  but the COMPILER will throw an error if some other function tries to access the
  variable. That means the variable is private to this function. Multiple calls
  to this function accessed the same variable in memory. */
  static int count = 1000000;
  count/=10;
  return count;
}

int main(){
  for (int i = 0; i < 4; i++){
    printf("%i\n", counter());
  }
  return 0;
}
