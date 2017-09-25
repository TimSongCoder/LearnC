#include <stdio.h>
#include <strings.h>

typedef struct {
  const char *description;
  float value;
} swag;

typedef struct {
  swag *swag;
  const char *sequence;
} combination;

typedef struct {
  combination numbers;
  const char *make;
} safe;

int main() {
  swag gold = {"GOLD!", 1000000.0};
  combination numbers = {&gold, "6502"};
  safe s = {numbers, "RAMACON250"};

  char input[5];
  puts("Input your password:");
  scanf("%4s", input);

  if(strcmp(numbers.sequence, input) == 0){
    printf("You got the %s worthing %.2f dollars!\n", gold.description, gold.value);
    printf("Get you to the string 'GOLD!' : %s\n", s.numbers.swag->description);
  }else{
    puts("Password is not matched! Try again!");
  }

  return 0;
}
