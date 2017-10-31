#include <stdio.h>
#include <netdb.h>

int main(){
  int stayopen = 1; /* Use a non-zero flag to keep the database open. */
  /* The setservent() function opens the services database to begin scanning it. */
  setservent(stayopen);
  struct servent *service;
  /* The getservent() function returns the next entry int the services database.
  If there are no more entries, it returns a null pointer. */
  int count = 0;
  while((service = getservent())){
    /* Retrieve the info about each service.
    Output the 'official' name, port number and associated protocol's name of the service. */
    printf("%s, %i, %s\n", service->s_name, service->s_port, service->s_proto);
    count++;
  }
  /* Close the services database. */
  endservent();
  printf("\nThere are %i entries in the services database in total.\n", count);
  return 0;
}
