#include <stdio.h>

int main(){
  int contestants[] = {1, 2, 3};
  int *choice = contestants;

  contestants[0] = 2; /* Set the first element to be 2. --> {2, 2, 3}*/
  contestants[1] = contestants[2]; /* Set the second element to be equal to 3.
  --> {2, 3, 3}*/
  contestants[2] = *choice; /* Modify the third element's value: this pointer
  variable points to the address of the first element in the
  contestants array (current value is 2). type compatibility issue? --> {2, 3, 2}*/

  printf("I'm going to pick contestant number %i\n", contestants[2]);
  return 0;
}
