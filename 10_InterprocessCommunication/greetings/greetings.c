#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void handle_interrupt(int signum){
  puts("Goodbye cruel world....\n");
  exit(1);
}

/* Register a handler for signal signum. */
int catch_signal(int signum, void (*handler)(int)){
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&(action.sa_mask));
  action.sa_flags = 0;
  return sigaction(signum, &action, NULL);
}

int main(){
  if(catch_signal(SIGINT, handle_interrupt) == -1){
    fprintf(stderr, "Can't register the handler for interrupt signal: %s\n", strerror(errno));
    exit(2);
  }
  char name[30];
  printf("Enter your name: ");
  fgets(name, 30, stdin);
  printf("Hello %s\n", name);
  return 0;
}
