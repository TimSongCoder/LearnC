#include <stdio.h>
#include "encrypt.h"

int main(){
  char pwd[20];
  puts("Input your favorite word for password: ");
  if(scanf("%19[^\n]s", pwd)){
    char origin[20];
    /* Copy the original word. */
    for(int i=0; i<sizeof(pwd); i++){
      origin[i] = pwd[i];
    }
    encrypt(pwd); /* Generate password through encrypting the original word. */
    fprintf(stdout, "Generated password: %s\nYou can regenerate it with the same word in case of you forget the password someday, so you only need to remember the word(%s).\n", pwd, origin);
  }else{
    fprintf(stderr, "Something wierd happened...\n");
    return 1;
  }
  return 0;
}
