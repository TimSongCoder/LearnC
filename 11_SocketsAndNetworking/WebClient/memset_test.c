#include <string.h>
#include <stdio.h>

int main(){
  int c = 65; /* Numeric value for 'A' in ASCII table. */
  char buf[] = "Day Day Up!";
  /* size_t strlen(const char *s); <string.h> 
  The strlen() function computes and returns the number of characters that
  precede the terminating NUL character. */
  size_t len = strlen(buf) - 1;

  printf("Original string: %s\n", buf);
  memset(buf, c, len);
  printf("String after being modified by memeset: %s\n", buf);

  return 0;
}
