#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

char* hostname = "www.learnersdictionary.com";
char* portnumber = "80";

void error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

/* Create a socket for remote server and attempt to connect it.
Note to check for errors. */
int open_socket(char *host, char *port){
  /* struct addrinfo [defined in <netdb.h>] {
    int ai_flags; [input flags]
    int ai_family;  [protocol family for socket]
    int ai_socktype;  [socket type]
    int ai_protocol;  [protocol for socket]
    socklen_t ai_addrlen; [length of socket-address]
    struct sockaddr *ai_addr; [socket-address for socket]
    char *ai_canonname; [canonical name for service location]
    struct addrinfo *ai_next; [pointer to next in list, linked-list data structure!]
    } */
  struct addrinfo *res;
  struct addrinfo hints;
  /* memset -- fill a byte string with a byte value, defined in string.h
  void* memset(void *b, int c, size_t len);
  The memset() function writes 'len' bytes of value 'c' (converted to an unsigned
  char) to the string 'b'.
  The memset() function returns its first argument. */
  memset(&hints, 0, sizeof(hints)); /*Clear the hints structure memory space.*/
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  /* getaddrinfo, freeaddrinfo -- socket address structure to host and service
  name. <netdb.h>

  int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints,
                  struct addrinfo **res); 'pointer to another pointer'
  The getaddrinfo() function is used to get a list of IP addresses and port numbers
  for host 'hostname' and service 'servname'. It is a replacement for and provide
  more flexibility than the gethostbyname() and getservbyname() functions.
  The 'hostname' and 'servname' arguments are either pointers to NUL-terminated
  strings or the null pointer. An acceptable value for 'hostname' is either a valid
  host name or a numeric host address string consisting of a dotted decimal IPv4 or
  an IPv6 address. The 'servname' is either a decimal port number or a service name
  listed in services. At least one of 'hostname' and 'servname' must be non-null.
  'hints' is an optional pointer to a struct addrinfo, as defined by <netdb.h>. This
  structure can be used to provide hints concerning the type of socket that the caller
  SUPPORTS or WISHES to use. The caller can supply the following structure elements
  in hints: ai_family, ai_socktype, ai_protocol, ai_flags. All other elements of
  the addrinfo structure passed via 'hints' MUST be zero or the null pointer.
  If the 'hints' is the null pointer, getaddrinfo() behaves as if the caller provided
  a struct addrinfo with ai_family set to PF_UNSPEC and all other elements set to
  zero or NULL.

  After a successful call to getaddrinfo(), '*res' is a POINTER to a linked list
  of one or more addrinfo structures. The list can be traversed by following the
  ai_next pointer in each addrinfo structure until a null pointer is encountered.
  The three members ai_family, ai_socktype, and ai_protocol in each returned addrinfo
  structure are suitable for a call to socket() function. For each addrinfo structure
  in the list, the ai_addr member points to a filled-in socket address structure
  of length ai_addrlen.
  All of the information returned by getaddrinfo() is dynamically allocated:
  the addrinfo structures themselves as well as the socket address structures and
  canonical host name strings included in the addrinfo structures. Memory allocated
  for the dynamically allocated structures created by a successful call to
  getaddrinfo() is released by the freeaddrinfo() function. The 'ai' pointer should
  be an addrinfo structure created by a call to getaddrinfo().

  getaddrinfo() returns zero on success or one of the predefined error codes if an
  error occurs.*/
  if (getaddrinfo(host, port, &hints, &res) != 0){
    /* Understand why we use pointer of pointer here! Make sure we manipulate the
    expected pointer variable to store the result list. */
    error("Can't resolve the address");
  }
  /* Use the first addrinfo structure from the returned list to create a socket. */
  int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(d_sock == -1){
    error("Can't open socket.");
  }
  /* Consistently use the first addrinfo structure. Indirect member access operatro -> usage. */
  int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res); /* Note the parameter type. */
  if(c == -1){
    error("Can't connect to socket for remote server.");
  }
  return d_sock;
}

/* Send message through the socket. Note to check the errors. */
int say(int socket, char *s){
  int result = send(socket, s, strlen(s), 0); /* socket, buffer, length, flags. */
  if(result == -1){
    fprintf(stderr, "%s: %s\n", "Error talking to the server", strerror(errno));
  }
  return result;
}

int main(int argc, char *argv[]){
  int d_sock;
  d_sock = open_socket(hostname, portnumber);
  char buf[255];

  sprintf(buf, "GET /definition/%s HTTP/1.1\r\n", argv[1]);
  say(d_sock, buf);

  say(d_sock, "Host: www.learnersdictionary.com\r\n\r\n"); /* You need a blank line to end the request string. */

  char rec[256];
  int bytesRecv = recv(d_sock, rec, 255, 0); /* Note the terminating NUL character. */
  while(bytesRecv){
    if(bytesRecv == -1){
      error("Can't read from server");
    }
    rec[bytesRecv] = '\0'; /* Terminate the string after valid content. */
    printf("%s", rec);
    bytesRecv = recv(d_sock, rec, 255, 0);
  }
  close(d_sock);

  return 0;
}
