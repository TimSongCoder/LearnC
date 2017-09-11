#include <stdio.h>

int main(){
  char food[5];
  puts("Enter favorite food: ");
  scanf("%s", food);
  /* The program will crash if scanf() writes data way beyond
   the end of the space allocated to the food array. */
  printf("Favorite food: %s\n", food);
  return 0;
}
