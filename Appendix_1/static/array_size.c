#include <stddef.h>
#include <stdio.h>

static const int values[] = {1, 2, 48, 681, 999};

/* Define a function-like macro to compute an array's size.
The sizeof operator must enclose its operand in parentheses when the operand is
a type name.
There are two cases where this arraysize compute technique does not work:
The first is where the array element has zero size: the denominator will be 0.
The second is where the array is in fact a function parameter: the numerator will
be sizeof pointer instead of sizeof array as expected, because the function parameter
merely passed in its value. */
#define ARRAYSIZE(x) (sizeof x / sizeof x[0])

int main(int argc, char *argv[]){
  /* size_t is an unsigned integer type used as an alias acrossing multiple OSs,
  whose actual data type varies from OS to OS. size_t is defined in <stddef.h>. */
  size_t i;
  /* Loop the values array. */
  for (i = 0; i < ARRAYSIZE(values); i++){
    printf("%d\n", values[i]);
  }
  return 0;
}
