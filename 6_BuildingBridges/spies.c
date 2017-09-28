#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct node just contains three pointers. It doesn't consume much space itself. */
typedef struct node {
  char *question;
  struct node *no;
  struct node *yes;
} node;

int yes_no(char *question){
  char answer[3];
  printf("%s? (y/n): ", question);
  fgets(answer, 3, stdin);
  return answer[0] == 'y';
}

node* create(char *question){
  node *n = malloc(sizeof(node));
  n->question = strdup(question);
  n->no = NULL;
  n->yes = NULL;
  return n;
}

void release(node *n){
  if(n){
    if(n->no)
      release(n->no);
    if(n->yes)
      release(n->yes);
    if(n->question)
      free(n->question);
    free(n);
  }
}

int main(){
  char question[80];
  char suspect[20];
  node *start_node = create("Does suspect have a mustache"); /* +2 blocks */
  start_node->no = create("Loretta Barnsworth"); /* +2 blocks */
  start_node->yes = create("Vinny the Spoon"); /* +2 blocks */

  node *current;
  do {
    current = start_node;
    while(1){
      if(yes_no(current->question)){
        if(current->yes){
          current = current->yes;
        }else{
          printf("SUSPECT IDENTIFIED\n");
          break;
        }
      }else if(current->no){
        current = current->no;
      }else{/* Answer is no but without valid no-node pointer. */
        /* Make the yes-node the new suspect name. */
        printf("Who's the suspect? ");
        fgets(suspect, 20, stdin);
        node *yes_node = create(suspect); /* +2 blocks */
        current->yes = yes_node; /* How about the old yes_node pointing node memory?
        Should release the old one if it is not NULL.*/

        /* Make the no-node a copy of this question. */
        node *no_node = create(current->question); /* +2 blocks */
        current->no = no_node; /* How about the old one? Should release the old one if it is not NULL. */

        /* Then REPLACE this question with the new question */
        printf("Give me a question that is TRUE for %s but not for %s? ",
                suspect, current->question);
        fgets(question, 80, stdin);
        current->question = strdup(question);
        /* How about the old question taking heap memory?
          +1 block, lost 1 block on the heap at the end of the program.*/

        break;
      }
    }
  }while(yes_no("Run again"));

  release(start_node); /* Only freed up 10 blocks in use. Lost one. */

  return 0;
}
