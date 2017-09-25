#include <stdio.h>

typedef union {
  float weight;
  int count;
} cupcake;

int main() {
  cupcake order = {2};
  /* By mistake, the programmer has set the WEIGHT, not the count.
  {.count = 2} is proper here.*/
  printf("Cupcakes quantity: %i\n", order.count);
  /* It reads a float from memory as int, which leads to a big problem!!! */
  return 0;
}
