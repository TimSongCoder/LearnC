#include <stdio.h>

int main(){
  char masked_raider[] = "Alive"; /* string literal 'Alive' lives in constant memory block,
   its value is copied to array masked_raider who lives in stack memeory. The constant
   can not be updated, it's READ-ONLY. While the array masked_raider living in stack can be
   modified as you want with its address in memory. */
  char *jimmy = masked_raider; /* pointer variable 'jimmy' store the address of the first
  element of array 'masked_raider' living in stack memory. */
  printf("Masked Raider is %s, Jimmy is %s\n", masked_raider, jimmy);

  masked_raider[0] = 'D';
  masked_raider[1] = 'E';
  masked_raider[2] = 'A';
  masked_raider[3] = 'D';
  masked_raider[4] = '!';
  /* You will access the same array actually whether through masked_raider array
   variable or jimmy pointer variable. */
  printf("Masked Raider is %s, Jimmy is %s\n", masked_raider, jimmy);

  /* jimmy and masked_raider are just aliases for the same memory address, they are
  pointing to the same place in memory. */
  return 0;
}
