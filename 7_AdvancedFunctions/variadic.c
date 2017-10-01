/* All the code to handle variadic functions is in the stdarg.h. */
#include <stdarg.h>
#include <stdio.h>

/* Use ellipsis after the last fixed argument to indicate there are more
arguments to come... */
void print_ints(int args, ...){
  /* A va_list will be used to store the extra arguments that are passed to your
  function. I guess it should be a struct :) */
  va_list ap;
  /* You need to tell the library the va_list used to store extra arguments and
  the name of the last fixed argument (i.e args in this case). */
  va_start(ap, args);
  int i;
  for (i = 0; i < args; i++) {
    /* Read extra arguments with va_arg() macro. va_arg() macro takes two
    values: the va_list and the type of the next argument. In this case, all of
    the arguments are ints. */
    printf("argument: %i\n", va_arg(ap, int));
  }
  /* After you've finished reading all of the arguments, you need to tell the
  library that you're finished. You do that with the va_end macro. */
  va_end(ap);
}

int main(){
  print_ints(3, 79, 101, 32);
  return 0;
}
