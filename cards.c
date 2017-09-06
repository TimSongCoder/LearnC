/* Program to evaluate face values.
   Example on Head First C book.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  char card_name[3];
  puts("Enter the card_name: ");
  scanf("%2s", card_name);
  int val = 0;
  /* Rewrite the sequence of if code using a switch statement.
  Single variable used in multiple test cases. */
  switch (card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
      val = 10;
      break;
    case 'A':
      val = 11;
      break;
    default:
      val = atoi(card_name);
  }
  printf("The card value is: %i\n", val);

  /*Check if the value is 3 to 6*/
  if (val>=3 && val<=6) {
    puts("Count has gone up");
  }else if(val==10){ /*Check if the card was 10, J, Q, or K.*/
    puts("Count has gone down");
  }

  return 0;
}
