#include <stdio.h>

int main(){
  float latitude, longitude;
  char info[80];
  while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3){
    if ((latitude > 26) && (latitude < 34)){ /* latitude is in the range. */
      if ((longitude > -76) && (longitude < -64)){ /* longitude is in the range. */
        printf("%f,%f,%s\n", latitude, longitude, info);
        /* Write the in range data to the standard output. */
      }
    }
  }

  return 0;
}
