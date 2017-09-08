#include <stdio.h>

int main() {
  int m = 100;
  int n = 103;
  int *address_of_m = &m;
  *address_of_m = *address_of_m + (n-m);

  printf("Current m value is: %i; Expected value is %i.\n", m, n);

  printf("int variable m is stored at: %p\n", address_of_m);
  printf("pointer variable address_of_m is stored at: %p\n", &address_of_m);
  return 0;
}
