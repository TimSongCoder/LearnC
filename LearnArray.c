#include <stdio.h>

int main(){
  int drinks[] = {4, 2, 3};
  printf("1st order: %i drinks\n", drinks[0]);
  printf("1st order: %i drinks\n", *drinks); /* dereference operation */
  if (drinks[0] == *drinks) {
    puts("drinks[0] == *drinks is TRUE! (drinks is an array variable.)");
  }

  printf("3rd order: %i drinks\n", drinks[2]);
  printf("3rd order: %i drinks\n", *(drinks + 2));
  /* pointer arithmetic, that's why array index starts from 0.*/
  if (drinks[2] == *(drinks + 2)) {
    puts("drinks[2] == *(drinks+2) is TRUE! (drinks is an array variable, pointer arithmetic demo.)");
  }
  return 0;
}
