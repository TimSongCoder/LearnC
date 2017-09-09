#include <stdio.h>

/* Use the power of pointer arithmetic to skip the first six characters of the msg. */
void skip(char *msg){
  puts(msg+6); /* output: call me*/
}

int main(){
  char *msg_from_amy = "Don't call me";
  skip(msg_from_amy);
  return 0;
}
