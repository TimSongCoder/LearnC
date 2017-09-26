#include <stdio.h>

typedef struct island {
  char *name;
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

int main() {
  /* Create islands in the planned tour... */
  island amity = {"Amity", "09:00", "17:00", NULL};
  island craggy = {"Craggy", "09:00", "17:00", NULL};
  island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
  island shutter = {"Shutter", "09:00", "17:00", NULL};
  /* link the islands together to form a tour. */
  amity.next = &craggy; /* A pointer to next island stop. */
  craggy.next = &isla_nublar;
  isla_nublar.next = &shutter;

  /* Change your mind and insert a new island stop in the middle of the tour... */
  island skull = {"Skull", "09:00", "17:00", NULL};
  /* Insert the island stop between isla_nublar and shutter. */
  isla_nublar.next = &skull;
  skull.next = &shutter;

  /* Call the display function to show the tour details. */
  display(&amity); /* We need to pass the address of the first island. */

  return 0;
}
