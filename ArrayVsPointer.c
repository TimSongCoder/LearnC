#include <stdio.h>

int main() {
  char s[] = "How big is it?";
  char *t = s;
  /* sizeof battle */
  printf("sizeof(array variable s): %lu bytes\n", sizeof(s)); /* 14 characters + end character \0 */
  printf("sizeof(pointer variable t): %lu bytes\n", sizeof(t)); /* A memory address number take 8 bytes space on 64 bit OS. */

  /* address battle */
  printf("Address of array variable s: %p\n", &s);
  printf("Value of pointer variable t: %p\n", t);
  printf("Address of pointer variable t: %p\n", &t);

  /* who am I? */
  if (s == &s) {
    puts("s == &s is true! (s is an array variable, which means that the address of an array variable is equal to itself.)");
  }
  if (t != &t) {
    puts("t != &t is true! (t is a pointer variable, who is storing the mentioned array's address. This means that a pointer variable has its own address.)");
  }
  return 0;
}
