#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
  char *feeds[] = {"http://www.autoguide.com/latest-articles.xml",
                   "http://www.nytimes.com/services/xml/rss/nyt/World.xml",
                   "https://www.nasa.gov/rss/dyn/breaking_news.rss"};
  int times = 3; /* The size of array is not easy to acquire in C... */
  char *phrase = argv[1]; /* The search term will be passed in as an argument. */
  int i;
  for (i = 0;i < times; i++){
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL}; /* Environment array. */

    pid_t pid = fork();
    /* The fork() causes creation of a new process. The new process(child process)
    is an exact copy of the calling process(parent process)except for the unique
    process ID and few other details.
    Upon successful completion, fork() returns a value of 0 to the child process
    and returns the process ID of the child process to the parent process.(They
    are running the same codes, so you can tell them through the return value and
    do your job accordingly.) Otherwise, a value of -1 is returned to the parent process, no child process is created,
    and the global variable errno is set to indicate the error. */
    if(pid == -1){
      fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
      return 1;
    }
    if(!pid){
      /* pid is 0, meaning that it's the child process. */
      if(execle("/usr/bin/python", "python", "./rssgossip.py", phrase, NULL, vars) == -1){
        fprintf(stderr, "Can't run script: %s\n", strerror(errno));
        return 1;
      }
      /* If the execle() system call succeeded, the current program will be stopped
      annd replaced by the new python program. */
    }else{
      /* In the parent process, the pid is the newly created child process's PID. */
      printf("I am the parent process and I have created a child process with PID=%i\n", pid);
    }
  }
  return 0;
}
