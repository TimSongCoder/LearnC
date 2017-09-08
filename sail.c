#include <stdio.h>

/* This method now has parameters type of pointers (int *), not integers.
 * The * operator can read/set the contents of a memory address (where the pointer variables point at).
 */
void go_south_east(int *lat_address, int *lon_address){
  *lat_address = *lat_address - 1;
  *lon_address = *lon_address + 1;
}

int main(){
  int latitude = 32;
  int longitude = -64;
  /* use Pointer Variables - variable storing address - to share memory across multiple functions.*/
  go_south_east(&latitude, &longitude);
  /* The & operator finds the address of a variable.*/
  printf("Avast! Now at: [%i, %i]\n", latitude, longitude);
  return 0;
}
