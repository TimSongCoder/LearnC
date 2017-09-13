#include <stdio.h>
#include <string.h>

void print_reverse(char *s){
  /* size_t is an unsigned integer type used to represent the sizes of objects.
  The result of the sizeof operator is of this type. On systems using the GNU C Library,
  this will be unsigned int or unsigned long int.
  size_t is the preferred way to declare any arguments or variables that hold
  the size of an object. */
  size_t len = strlen(s); /* The strlen() function returns the number of characters
  that precede the terminating NUL character. */

  char *t = s + len - 1; /* Figure out the address of the last character. */

  while(t >= s){ /* Loop from the last character to the first character. */
    printf("%c", *t);
    t = t - 1; /* pointer arithmetic */
  }
  puts("");
}

int main(){
  char input[30];
  puts("Input your words: ");
  fgets(input, 30, stdin); /* As we use fgets() you will see a newline character
  comes before any other characters if your input content is less than 29 characters.
  But that's not bad in this case:) */

  print_reverse(input);

  return 0;
}
