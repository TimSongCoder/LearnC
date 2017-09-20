#include <stdio.h>
#include "encrypt.h" /* Note the quotes usage. */

int main(){
  char msg[80];
  while (fgets(msg, 80, stdin)) {
    encrypt(msg);
    printf("%s\n", msg);
    puts("+++++++++++++++++++");
  }
}
