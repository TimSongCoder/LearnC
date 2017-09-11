#include <stdio.h>

/* A variable points to a string literal can't be used to change the contents of the string. */
int main(){
  char *cards = "JQK"; /* Note: cards here is a pointer variable, not an array variable. */
  char a_card = cards[2]; /* a_card: K*/
  cards[2] = cards[1]; /* JQK --> JQQ */
  cards[1] = cards[0]; /* JQQ --> JJQ */
  cards[0] = cards[2]; /* JJQ --> QJQ */
  cards[2] = cards[1]; /* QJQ --> QJJ */
  cards[1] = a_card;   /* QJJ --> QKJ */
  puts(cards);

  return 0;
}
