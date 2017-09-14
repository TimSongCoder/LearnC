#include <stdio.h>
#include <string.h>

void print_reverse(char input[]){
  size_t len = strlen(input);
  char *t = input + len -1; /* Address for the last character of the input string. */
  while (t>=input) {
    printf("%c", *t);
    t = t - 1;
  }
  printf("\n");
}

int main(){
  /* array of pointers. */
  char *juices[] = {
    "dragonfruit", "waterberry", "sharonfruit", "uglifruit", /* 0 1 2 3 */
    "rumberry", "kiwifruit", "mulberry", "strawberry", /* 4 5 6 7 */
    "blueberry", "blackberry", "starfruit" /* 8 9 10 */
  };
  char *a;

  puts(juices[6]); /* mulberry */

  print_reverse(juices[7]); /* strawberry --> yrrebwarts */

  a = juices[2]; /* a -> sharonfruit constant */
  juices[2] = juices[8]; /* element at index 2 is set to be address of 'blueberry' */
  juices[8] = a; /* element at index 8 is set to be address of 'sharonfruit' */
  /* The three lines of code above actually swap the elements at index 2 and 8. */
  puts(juices[8]); /* sharonfruit */

  print_reverse(juices[(18+7)/5]); /* juices[5] -> kiwifruit --> tiurfiwik */

  puts(juices[2]); /* blueberry */

  print_reverse(juices[9]); /* blackberry --> yrrebkcalb */

  juices[1] = juices[3]; /* element at index 1 is set to be address of uglifruit. */
  puts(juices[10]); /* starfruit */

  print_reverse(juices[1]); /* uglifruit --> tiurfilgu */

  return 0;
}
