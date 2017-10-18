#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int score = 0;

void end_game(int sig){
  printf("\nFinal score: %i\n", score);
  exit(0);
}

/* We pass the signal handler function's pointer in. */
int catch_signal(int sig, void (*handler)(int)){
  struct sigaction action;
  action.sa_handler = handler;
  /* Empty the blocking signal set. Note the argument type is pointer. */
  sigemptyset(&(action.sa_mask));
  action.sa_flags = 0; /* No extra flags intended. */
  return sigaction(sig, &action, NULL); /* Note the argument type. */
}

void times_up(int sig){
  puts("\nTIME'S UP!");
  raise(SIGINT); /* Signal escalation. */
}

void error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main(){
  /* Register the handlers for SIGALRM and SIGINT signals. */
  catch_signal(SIGALRM, times_up);
  catch_signal(SIGINT, end_game);
  /* time_t time(time_t *result) return the current calendar time.
  If the result argument is not a null pointer, the current calendar time will be
  stored in time_t result points to, too.*/
  srandom(time (0));
  /* void srandom(unsigned int seed)
  The srandom function sets the state of the random number generator based on
  the integer seed. If you supply a seed value of 1, this will cause the random
  function to reproduce the default set of random numbers. To produce a different
  set of pseudo-random numbers each time your program runs, do srandom (time (0)),
  use the current time as the seed value. */
  while(1){
    /* long int random(void)
    This function returns the next pseudo-random number in the SEQUENCE.
    RANGE from 0 to 2147483647. */
    int a = random() % 11;
    int b = random() % 11;
    /* a and b will be random numbers between 0 and 10, remainder of 11. */
    char txt[4];
    /* Set a timer for quiz. included in <unistd.h>. unsigned alarm(unsigner seconds)
    The alarm() function sets a timer to deliver the signal SIGALRM to the calling
    process after the specified number of seconds.
     As long as you go through the loop in less than 5 seconds, the timer will
     be reset and it will never fire. */
    alarm(5);
    printf("\nWhat is %i times %i?", a, b);
    fgets(txt, 4, stdin); /* May include the line-terminating charater. */
    int answer = atoi(txt);
    /* The int atoi(const char *str) function converts the initial portion of the
    string pointed to by str to int representation. Why say initial portion, because
    the terminating NUL character? I guess:) */
    if (answer == a*b){
      score++;
    }else{
      printf("\nWrong! Score: %i\n", score);
    }
  }
  return 0;
}
