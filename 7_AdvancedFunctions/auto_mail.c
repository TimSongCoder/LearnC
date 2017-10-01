#include <stdio.h>

/* When C creates an enum, it gives each of the symbols a number starting at 0.
  i.e 0, 1, 2 in this case for DUMP, SECOND_CHANCE, and MARRIAGE. */
typedef enum {DUMP, SECOND_CHANCE, MARRIAGE} response_type;

typedef struct{
  char *name;
  response_type type;
} response;

void dump(response r){
  printf("Dear %s, \n", r.name);
  puts("Unfortunately your last date contacted us to");
  puts("say that they will not be seeing you again");
}

void second_chance(response r){
  printf("Dear %s, \n", r.name);
  puts("Good news: your last date has asked us to");
  puts("arrange another meeting. Please call ASAP.");
}

void marriage(response r){
  printf("Dear %s, \n", r.name);
  puts("Congratulations! Your last date has contacted");
  puts("us with a proposal of marriage.");
}

/* Create an array of function pointers global variable.
   Note: it contains a set of function names that are in exactly the same ORDER
   as the types in the enum. That's why we can use the enum's numeric value as
   the index to access this array's elements. */
void (*replies[])(response) = {dump, second_chance, marriage};

int main(){
  response r[] = {
    {"Mike", DUMP}, {"Luis", SECOND_CHANCE},
    {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}
  };
  int i;
  for (i = 0; i < 4; i++) {
    /* The switch logic code is not easy to cope with the change of
    response_type enum. If the enum changes, every switch block like this
    need to be changed subsequentially. That's a pain too.

    Use array of function pointers instead.*/
    replies[r[i].type](r[i]);
    /* Because of our replies' definition order, we can use the enum type as
    array index conveniently. */
  }

  return 0;
}
