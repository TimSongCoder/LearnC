#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
  char *name; /* Use char pointer instead of char array because of its more flexible length/size. */
  char *opens;
  char *closes;
  struct island *next; /* Here you can see why you MUST set a struct name for recursive structure. */
} island; /* This struct has an alias being the same to its name. */

void display(island *start){
  island *i = start;
  /* i and start variable are both struct pointers, we can not use dot notation
  on them directly. */
  for(; i != NULL; i = i->next) {
    printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
  }
}

island* create(char *name){
  island *i = malloc(sizeof(island));
  i->name = strdup(name);
  /* Use strdup() function: allocate sufficient space in heap memory and copy the string content into it,
  then return the pinter to it. You need to release the memory too. */
  i->opens = "09:00";
  i->closes = "17:00";
  i->next = NULL;
  return i;
}

/* Release the memory used by a linked list start by parameter 'start'. */
void release(island *start){
  island *i = start;
  island *next = NULL;
  for(; i != NULL; i = next){
    next = i->next;
    /* Release name string memory created by strdup() and struct memory created by malloc(). */
    free(i->name);
    free(i);
  }
}

int main() {
  island *start = NULL;
  island *i = NULL;
  island *next = NULL;
  char name[80];
  /* Note the fgets() function logic: it reads at most one less than the number of
  characters specified by size from the given stream and stores them in the string str.
  Reading stops when a newline character is FOUND, at the end-of-file or error. */
  for(; fgets(name, 80, stdin) != NULL; i = next){ /* Assign a new value to pointer i each iteration. */
    next = create(name);
    if (start == NULL)
      start = next;
    if(i != NULL){ /* Check the old pointer value. */
      i->next = next;
    }
  }
  display(start);

  /* Free the memory when you are done! */
  release(start);

  return 0;
}
