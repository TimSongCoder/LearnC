#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
  char *feeds[] = {"https://www.nasa.gov/rss/dyn/breaking_news.rss",
                   "http://www.nytimes.com/services/xml/rss/nyt/World.xml",
                   "https://www.nasa.gov/rss/dyn/breaking_news.rss"};
  int times = 3; /* The size of array is not easy to acquire in C... */
  char *phrase = argv[1]; /* The search term will be passed in as an argument. */
  int i;
  for (i = 0;i < times; i++){
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL}; /* Environment array. */
    /* If the execle() system call succeeded, the current program will be stopped
    annd replaced by the new python program, this is where bugs emerged, you can
    not loop all the rss feeds, actually it will only search in one rss feed source. */
    if(execle("/usr/bin/python", "python", "./rssgossip.py", phrase, NULL, vars) == -1){
      fprintf(stderr, "Can't run script: %s\n", strerror(errno));
      return 1;
    }
  }
  return 0;
}
