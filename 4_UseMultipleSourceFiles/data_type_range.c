#include <stdio.h>
#include <limits.h> /* This contains the values for the integer types like int and char. */
#include <float.h> /* This contains the values for floats and doubles. */

int main(){
  printf("The value of INT_MAX is %i\n", INT_MAX);
  printf("The value of INT_MIN is %i\n", INT_MIN);
  printf("An int takes %zi bytes\n", sizeof(int));

  printf("The value of FLT_MAX is %f\n", FLT_MAX);
  printf("The value of FLT_MIN is %.50f\n", FLT_MIN);
  printf("A float takes %zi bytes\n", sizeof(float));
}
