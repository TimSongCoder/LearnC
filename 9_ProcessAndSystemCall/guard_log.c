#include <time.h>
#include <stdio.h>
#include <stdlib.h>

char* now(){
  time_t t;
  time (&t);
  return asctime(localtime (&t));
}

int main(){
  char comment[80];
  char cmd[120];
  fgets(comment, 80, stdin);
  /* The printf() family of functions produces output according to a format as
  described below. sprintf(), snprintf(), vsprintf(), and vsnprintf() write to
  the character string str.
  sprintf(char * restrict str, const char * restrict format, ...) */
  sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());
  /* Use >> to append comment log. */

  system(cmd);
  /* system(const char *command): PASS a command to the shell. #include <stdlib.h>
  The system() function hands the command to the command interpreter sh(1).
  The calling process waits for the shell to finish executing the command,
  ignoring SIGINT and SIGQUIT, and blocking SIGCHILD. */
  return 0;
}
