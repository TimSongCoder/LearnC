/* Explore the sizeof operator's behavior. */

#include <stdio.h>

void msg_size(char msg[]){
  printf("[%s] occupies %lu bytes\n", msg, sizeof(msg));
  /* sizeof on array function parameter will return size of
  'char *' instead of 'char []' -- Wsizeof-array-argument */
}

int main() {
  char msg[] = "Turtles!"; /* Size should be 9: 8 characters plus a \0 end character.*/
  printf("[%s] occupies %lu bytes\n", msg, sizeof(msg)); /* size value 9 */
  printf("The msg variable value is stored at: %p\n", msg);
  /* We pass the msg directly here, compiler did not complain about it,
  that means we can use array variable like a pointer.*/
  puts("\nCall msg_size function:\n");
  msg_size(msg); /* size value 8 */
  return 0;
}
