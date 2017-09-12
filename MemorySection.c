#include <stdio.h>

void some_func(){
  int some_func_in_stack_0 = 6;
  int some_func_in_stack_1 = 7;

  printf("some_func: int0: %p, int1: %p\n", &some_func_in_stack_0, &some_func_in_stack_1);
}

int main(){
  char *const_demo = "JQK";
  int main_in_stack_0 = 4;
  int main_in_stack_1 = 5;
  char main_arr[] = "Main Array";

  printf("main: Pointer(to constant): %p, int0: %p, int1: %p, Array: %p\n", const_demo,
        &main_in_stack_0, &main_in_stack_1, main_arr);

  some_func();

  return 0;
}
