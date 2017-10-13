#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  char *my_env[] = {"FOOD=coffee", NULL};
  /* Use system call exec() function to call another program.
  As per the execle() function, the first argument is program's fullpath,
  the first command-line argument can be program file name without path specified.*/
  if(execle("./coffee", "coffee", "donuts", NULL, my_env) == -1){
    fprintf(stderr, "Can't create order: %s\n", strerror(errno));
    return 1;
  }
  return 0;
}
