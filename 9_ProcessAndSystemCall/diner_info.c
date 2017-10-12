#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  printf("Diners: %s\n", argv[1]);
  printf("Juice: %s\n", getenv("JUICE"));
  /* getenv() in stdlib.h lets you read environment variables. */

  return 0;
}
