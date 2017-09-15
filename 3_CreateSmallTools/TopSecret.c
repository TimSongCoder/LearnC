#include <stdio.h>

int main(){
  char word[10];
  int i = 0;
  /* %9s conversion restrict: the input string will STOP at white space OR at
  the maximum field width, whichever occurs first. */
  while(scanf("%9s", word) == 1){
    i = i + 1;
    if(i % 2){ /* i = 1, 3, 5, 7, ... */
      fprintf(stdout, "%s\n", word);
      /* stdout is redirected to message1.txt */
    }else{ /* i = 2, 4, 6, 8, ... */
      fprintf(stderr, "%s\n", word);
      /* stderr is redirected to message2.txt */
    }
  }

  return 0;
}
