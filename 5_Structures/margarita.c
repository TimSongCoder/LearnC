#include <stdio.h>

typedef union {
  float lemon;
  int lime_pieces;
} lemon_lime;

typedef struct {
  float tequila;
  float cointreau;
  lemon_lime citrus;
} margarita;

int main() {
  margarita m = {2.0, 1.0, {2}};

  printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n",
          m.tequila, m.cointreau, m.citrus.lemon);
  /* Exercise candidates: 1, 4, 5, 6
  Exercise A: 6
  Exercise B: 1
  Exercise C: 4
  */

  puts("* * * * * Dividing Line * * * * *");

  margarita mm = {2.0, 1.0, {.lime_pieces=1}};
  printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%i pieces of lime\n",
          mm.tequila, mm.cointreau, mm.citrus.lime_pieces);

  /* Exercise D: union data initialization & update syntax. */
  margarita test;
  test = {2.0, 1.0, {0.5}};
  
  return 0;
}
