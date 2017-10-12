#include <unistd.h> /* You need this for exec() functions. */
#include <errno.h> /* You need this for errno variable. */
#include <stdio.h> /* You need this for fprintf() funciton. */
#include <string.h> /* You need this for strerror() function. */

int main(){
  /* If any of the exec() functions returns, an error will have occurred. The
  return value is -1, and the global variable errno will be set to indicate the
  error.
  You can use the strerror() function in string.h to convert an error number into
  a message. */
  if(execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1){
    /* System call execl() with full path of the targeting program file. */
    if(execlp("ipconfig", "ipconfig", NULL) == -1){
      /* No path specified explicitly, it will search in the standard/default COMMAND PATH. */
      fprintf(stderr, "Cannot run ipconfig: %s", strerror(errno));
      return 1;
    }
  }

  return 0;
}
