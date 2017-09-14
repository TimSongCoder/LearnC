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

    if (latitude < -90 || latitude > 90) {
      printf("The latitude value (%f) is out of valid range [-90, 90]\n", latitude);
      return 2;
    }else if(longitude < -180 || longitude > 180){
      printf("The longitude value (%f) is out of valid range [-180, 180]\n", longitude);
      return 2;
    }

    printf("{latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
  }
  puts("\n]");

  return 0;
}
