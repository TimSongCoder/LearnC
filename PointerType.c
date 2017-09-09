#include <stdio.h>

int main(){
  int nums[] = {1, 2, 3};
  printf("nums is at: %p\n", nums);
  printf("nums+1 is at: %p\n", nums+1);
  printf("sizeof(int) is: %lu bytes\n", sizeof(int));

  /* Expose the pointer arithmetic secret! */
  long index0_address = (long)nums; /* Cast the pointer to long integer before we do the subtraction. */
  long index1_address = (long)(nums+1);
  printf("The address value index0_address and index1_address is %lu and %lu respectively.\n", index0_address, index1_address);
  if(sizeof(int) == (index1_address - index0_address)){
    puts("sizeof(int) == (index1_address - index0_address) is TRUE!!!");
    puts("Now you see why pointer type matters! Pointer types exist so that the compiler knows how much to adjust the pointer arithmetic.");
  }

  return 0;
}
