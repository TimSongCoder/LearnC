#include <stdio.h>
#include <string.h>

char tracks[][80] = {
  "I left my heart in Harvard Med School",
  "Newark, Newark - a wonderful town",
  "Dancing with a Dork",
  "From here to maternity",
  "The girl from Iwo Jima"
};

/* The find_track function needs to come first, BEFORE you call it from main. */
void find_track(char search_for[]){
  int i;
  for(i = 0; i < 5 ; i++){
    if(strstr(tracks[i], search_for)){
      printf("Track %i: '%s'\n", i, tracks[i]);
    }
  }
}

int main(){
  char search_for[80];
  printf("Search for: ");
  fgets(search_for, 80, stdin);/* fgets(str, size, stream) is used to get a line from a stream.
  The function reads at most one less than the number of characters specified by size
  from the given stream and stores them in the string str.
  Reading stops when a newline character is found, at end-of-file or error.
  The newline, if any, is RETAINED.
  If any chracters are read and there is no error, a '\0' character is appended
  to end the string.
  The gets() function is equivalent to fgets() with an infinite size and a stream of stdin,
  except that the newline character (if any) is NOT stored in the string. It is the
  caller's responsibility to ensure that the input line, if any, is sufficiently
  short to fit in the string. */
  find_track(search_for);
  return 0;
}
