#include <stdio.h>
#include <string.h>

int main(){
  char s0[] = "dysfunctional";
  char s1[4];
  puts("Input your search content (3 characters limited): ");
  fgets(s1, sizeof(s1), stdin); /* Use the second argument to limit the number of valid characters. */
  char *location = strstr(s0, s1); /* It will return the address of the located
  string in memory if it finds the string. It will return 0 otherwise. */

  /* C treats 0 as false.
  So you can use strstr() to check for existence of one string inside another. */
  if (location) {
    printf("I found the %s in %s\n", s1, s0);
  }else{
    puts("Counld not find match...");
  }
  printf("Location value: %p\n", location);

  return 0;
}
