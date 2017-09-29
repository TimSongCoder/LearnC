#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Comparaters' return value result determine the order:
if result < 0, score_a -> score_b
if result == 0, score_a -> score_b
if result > 0, score_b -> score_a */

int compare_scores(const void* score_a, const void* score_b){
  int a = *(int*)score_a;
  int b = *(int*)score_b;
  return a - b;
}

int compare_scores_desc(const void* score_a, const void* score_b){
  int a = *(int*)score_a;
  int b = *(int*)score_b;
  return b - a;
}

typedef struct {
  int width;
  int height;
} rectangle;

int compare_areas(const void* recA, const void* recB){
  rectangle *a = (rectangle*)recA;
  rectangle *b = (rectangle*)recB;
  return a->width * a->height - b->width * b->height;
}

/* When qsort() calls the comparator function, it sends POINTERS to two elements
in the arrays. In this case, we got an array of char pointers, so parameters a,b
are pointers to pointers. */
int compare_names(const void* a, const void* b){
  char* strA = *(char**)a;
  char* strB = *(char**)b;
  return strcmp(strA, strB); /* strcmp() function needs values of type char*. */
}

int compare_areas_desc(const void* a, const void* b){
  return compare_areas(b, a);
}

int compare_areas_names(const void* a, const void* b){
  return compare_names(b, a);
}

int main(){
  int scores[] = {543, 323, 32, 554, 11, 3, 112};
  int i;
  /* void qsort(void *base, size_t nel, size_t width,
                int (*compar)(const void *, const void *));
  The qsort() function sorts an array of nel objects, the initial member of
  which is pointed to by base. The size of each object is specified by width.
  The contents of the array base are sorted in ASCENDING order according
  to a comparison function pointed to by compar, which requires two arguments
  POINTING to the objects being compared.
  The comparsion function must return an integer less than, equal to, or larger
  than zero if the first argument is CONSIDERED to be respectively less than,
  equal to, or greater than the second.*/
  qsort(scores, 7, sizeof(int), compare_scores_desc);
  puts("These are the scores in order:");
  for (i = 0; i < 7; i++){
    printf("Score = %i\n", scores[i]);
  }

  /* names is an array of char pointers, which are pointing to char data resides
   in constants memory section. */
  char *names[] = {"Karen", "Mark", "Brett", "Molly"};
  qsort(names, 4, sizeof(char*), compare_names);
  puts("These are the names in order:");
  for (i=0; i < 4; i++){
    printf("%s\n", names[i]);
  }

  return 0;
}
