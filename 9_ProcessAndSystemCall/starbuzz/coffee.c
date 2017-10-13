#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  char *w = getenv("EXTRA");
  /* The getenv() function returns the value of the environment variable as a
  NUL-terminated string. If the variable name is not in the current environment,
  NULL is returned. */
  if(!w){
    w = getenv("FOOD");
  }
  if(!w){
    w = argv[argc - 1];
  }
  char *c = getenv("EXTRA");
  if(!c){
    c = argv[argc - 1];
  }
  printf("%s with %s\n", c, w);
  return 0;
}
