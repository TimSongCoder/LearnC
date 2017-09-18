#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if(argc != 6){ /* The first argument contains the name of the program. */
    fprintf(stderr, "You need to give 5 arguments\n");
    return 1;
  }

  char line[80];

  /* Safety Check for fopen function ("IO exceptions"):
     Upon successful completion, it returns a FILE pointer.
     Otherwise, NULL is returned and the global variable errno
     is set to indicate the error.
  */
  FILE *in = fopen("spooky.csv", "r");
  FILE *file1 = fopen(argv[2], "w");
  FILE *file2 = fopen(argv[4], "w");
  FILE *file3 = fopen(argv[5], "w");

  while(fscanf(in, "%79[^\n]\n", line) == 1){
    if(strstr(line, argv[1])){
      fprintf(file1, "%s\n", line);
    }else if(strstr(line, argv[3])){
      fprintf(file2, "%s\n", line);
    }else{
      fprintf(file3, "%s\n", line);
    }
  }

  /* Close all the data streams when you are finished using them. */
  fclose(in);
  fclose(file1);
  fclose(file2);
  fclose(file3);

  return 0;
}
