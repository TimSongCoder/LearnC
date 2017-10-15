#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
  /* The exit() funciton (included in stdlib.h) causes normal process termination
  and the value of status & 0377 is returned to the parent.*/
}

int main(int argc, char *argv[]){
  char *phrase = argv[1];
  char *vars[] = {"RSS_FEED=http://www.autoguide.com/latest-articles.xml", NULL};
  FILE *f = fopen("stories.txt", "w");
  /* The fopen() function opens the file whose name is the string pointed to by
  path and associates a stream with it.
  Upon successful completion fopen() returns a FILE pointer. Otherwise, NULL is
  returned and errno is set to indicate the error.*/
  if(!f){
    error("Can't open stories.txt");
  }
  pid_t pid = fork();
  if (pid == -1){
    error("Can't fork process");
  }
  if(!pid){
    if(dup2(fileno(f), 1) == -1){
      /* The dup2(int oldfd, int newfd) system call creates a copy of the file
      descriptor oldfd, using the descriptor number specified in newfd. If the
      descriptor newfd is previously open, it is silently closed before being
      reused. On success, this system call return the new descriptor. On error,
      -1 is returned, and errno is set appropriately.
      The function fileno(FILE *stream) examines the argument stream and returns
      its integer descriptor. */
      error("Can't redirect Standard Output");
    }
    if(execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py",
              phrase, NULL, vars) == -1){
      error("Can't run script");
    }
    return 0;
  }
}
