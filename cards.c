/* Program to evaluate face values.
   Example on Head First C book.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  char card_name[3];
  int count = 0;
  while(card_name[0]!='X'){
    int val = 0;
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
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
      case 'X':
        continue;
      default:
        val = atoi(card_name);
        if (val>10 || val<1) {
          puts("Input card value is outside of the valid range: 1-10, inclusive.");
          continue;
        }
    }
    /*Check if the value is 3 to 6*/
    if (val>=3 && val<=6) {
      puts("Count has gone up");
      count++;
    }else if(val==10){ /*Check if the card was 10, J, Q, or K.*/
      puts("Count has gone down");
      count--;
    }
    printf("The card value is: %i\n", val);
    printf("Current count: %i\n", count);
  }

  return 0;
}
