#include <stdarg.h>
#include <stdio.h>

typedef enum {
  MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE
} drink;

/* Gets the price for individual drink. */
double price(drink d){
  switch (d) {
    case MUDSLIDE:
      return 6.79;
    case FUZZY_NAVEL:
      return 5.31;
    case MONKEY_GLAND:
      return 4.82;
    case ZOMBIE:
      return 5.89;
  }
  return 0;
}

double total(int count, ...) {
  double total = 0;
  va_list args;
  va_start(args, count);
  for(int i = 0; i < count; i++){
    total += price(va_arg(args, drink));
  }
  va_end(args);
  return total;
}

int main(){
  printf("Total price is %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE));
  printf("Total price is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
  printf("Total price is %.2f\n", total(1, ZOMBIE));
  return 0;
}
