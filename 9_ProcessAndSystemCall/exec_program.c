#include <unistd.h>

int main(){
  /* You can create a set of environment variables as an array of string
  pointers, the last item must be NULL. */
  char *my_env[] = {"JUICE=peach and apple", NULL};
  /* LIST exec() function: execle(), declared in unistd.h header file.
  Paramerters: program name, command-line arguments, environment variables. */
  execle("diner_info", "diner_info", "4", NULL, my_env);

  return 0;
}
