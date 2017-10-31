#include <netdb.h>
#include <stdio.h>

int main(){
  struct servent *adb_serv;
  /* The getservent(), getservbyname(), getservbyport() functions defined in netdb.h
  each return a pointer to an servent struct object, which containing the broken-out
  fields of a line in the network services data base.
  So you CAN NOT use these functions to query or investigate arbitrary running
  service or busy ports. */
  adb_serv = getservbyname("adb", "TCP");
  if(adb_serv){
    printf("%s, %i, %s\n", adb_serv->s_name, adb_serv->s_port, adb_serv->s_proto);
  }else{
    puts("Can't find the adb service.");
  }
  return 0;
}
