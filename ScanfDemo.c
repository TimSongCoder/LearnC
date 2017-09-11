#include <stdio.h>

int main(){
  int age;
  char first_name[20], last_name[20];
  puts("Enter your full name and age: (Format: First_name Last_name Age)");
  scanf("%19s %19s %i", first_name, last_name, &age); /* Format just works like printf function. */
  /* Why use &age here?
     Functions need the variable's address to update its content/value.
  */
  printf("First: %s Last: %s, Age: %i\n", first_name, last_name, age);
}
