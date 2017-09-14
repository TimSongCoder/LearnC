#include <stdio.h>

int main(){
  float latitude, longitude;
  char info[80];
  int started = 0;

  puts("data=[");
  /* The family of scanf functions return the number of input items assigned.
  This can be fewer than provided for, or even zero, in the event of a matching
  failure. The %79[^\n] conversion format to accept only one line of characters,
   with maximum of 79 limit.
   This function require pointers as variable arguments. */
  while(scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3){
    if(started){
      printf(",\n");
    }else{
      started = 1;
    }
    printf("{latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
  }
  puts("\n]");

  return 0;
}
