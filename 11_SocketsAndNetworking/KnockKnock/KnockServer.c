#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void error(char *msg){
  fprintf(stderr, "%s : %s", msg, strerror(errno));
  exit(1); /* exit() function is defined in <stdlib.h> */
}

int listener_desc;

void handle_shutdown(int sig){
  if(listener_desc && listener_desc!=-1){
    close(listener_desc);
  }
  fprintf(stderr, "Bye!\n");
  exit(0);
}

/* Send a message to a client. */
int say(int socket, char *msg){
  /* send, sendmsg, sendto -- send a message from a socket. <sys/socket.h>

  ssize_t send(int socket, const void *buffer, size_t length, int flags);

  send(), sendto(), and sendmsg() are used to transmit a message to another socket.
  send() may be used ONLY when the socket is in a 'connected' state, while sendto()
  and sendmsg() may be used at any time.

  The length of the message is given by 'length'. If the message is too long to
  pass ATOMICALLY through the underlying protocol, the error EMSGSIZE is returned,
  and the message is not transmitted.

  No indication of failure to deliver is implicit in a send(). Locally detected
  errors are indicated by a return value of -1.

  If no message space is available at the socket to hold the message to be transmitted,
  then send() normally blocks, unless the socket has been placed in non-blocking
  I/O mode. The select() call may be used to determine when it is possible to send
  more data.

  The 'flags' parameter may include one or more of the following:
    MSG_LOOB, MSG_DONTROUTE

  Upon successful completion, the number of bytes which were sent is returned.
  Otherwise, -1 is returned and the global variable errno is set to indicated the
  error.
  */
  int result = send(socket, msg, strlen(msg), 0);
  if(result == -1){
    /* Don't call error() if you won't stop the server becase of problem associated
    with one client. */
    fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
  }
  return result;
}

int read_in(int socket, char *buf, int len){
  char *s = buf;
  int slen = len;
  /* recv, recvfrom, recvmsg -- receive a message from a socket. <sys/socket.h>

  ssize_t recv(int socket, void *buffer, size_t length, int flags);

  ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags,
                   struct sockaddr *restrict address, socklen_t *restrict address_len);

  ssize_t recvmsg(int socket, struct msghdr *message, int flags);

  The recvfrom() and recvmsg() SYSTEM calls are used to receive messages from a
  socket, and may be used to receive data on a socket whether or not it is
  connection-oriented.

  If 'address' is not a null pointer and the socket is not connection-oriented,
  the 'source address' of the message is filled in. The 'address_len' argument is
  a value-result argument, initialized to the size of the buffer associated with
  'address', and modified on return to indicate the actual size of the address
  stored there.

  The recv() function is normally used only on a CONNECTED socket and is identical
  to recvfrom() with a null pointer passed as its 'address' argument. As it is
  redundant, it may not be supported in future release.

  All three routines return the length of the message on successful completion.
  If a message is too long to fit in the supplied buffer, excess bytes may be discarded
  depending on the type of socket the messages is received from.

  If no messages are availabe at the socket, the receive call waits for a message
  to arrive, unless the socket is nonblcking in which case the value -1 is returned.
  The receive calls normally return any data available, up to the requested amount,
  RATHER THAN waiting for receipt of the full amount requested; this behavior is
  affected by the socket-level options SO_RCVLOWAT and SO_RCVTIMEO.

  The select() system call may be used to determine when more data arrive.

  If no messages are available to be received and the peer has performed an
  orderly shutdown, the value 0 is returned.

  The 'flags' argument to a recv() function is formed by or'ing one or more of the
  values (bitwise OR operations): MSG_OOB, MSG_PEEK, MSG_WAITALL.

  The recvmsg() system call uses a 'msghdr' structure to minimize the number of
  directly supplied arguments.

  These calls return the number of bytes received, or -1 if an error occured. For
  TCP sockets, the return value 0 means the peer has closed its half side of
  the connection. */
  int c = recv(socket, s, slen, 0);
  while (c > 0 && s[c-1] != '\n'){
    s += c; /* pointer arithmetic */
    slen -= c; /* decrease the buffer size accordingly. */
    c = recv(socket, s, slen, 0); /* This may block the process. */
  }
  if(c < 0){
    return c; /* Error case. */
  }else if(c == 0){ /* Connection closed. Send back an empty string. */
    buf[0] = '\0';
  }
  return len - slen; /* The actual number of bytes received. */
}

int main(){
  struct sigaction action, old_action;
  action.sa_handler = handle_shutdown;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if(sigaction(SIGINT, &action, &old_action) == -1) {
    error("Can't set the interrupt handler");
  }

  /* int socket(int domain, int type, int protocol)
  This function creates an endpoint for communication and returns a descriptor.

  The domain parameter specifies a communication domain within which communication
  will take place; this selects the PROTOCOL family which should be used.

  The socket has the indicated 'type', which specifies the semantics of communication.

  The 'protocol' specifies a particular protocol to be used with the socket. Normally
  only a single protocol exists to support a particular socket type within a given
  protocol family. However, it is possible that many protocols may exist, in which
  case a particular protocol must be specified in this manner. The protocol number
  to use is particular to the communication domain in which communication is to
  take space.

  The operation of sockets is controlled by SOCKET LEVEL OPTIONS.

  A -1 is returned if an error occurs, otherwise the return value is a descriptor
  referencing the socket. */
  listener_desc = socket(PF_INET, SOCK_STREAM, 0);
  if(listener_desc == -1){
    error("Can't open socket");
  }

  /* struct sockaddr_in is the data type used to represent socket addresses in
  the Internet namespace. It is defined in the header file netinet/in.h */
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  /* htonl, htons, ntohl, ntohs -- convert values between host and network byte order, <arpa/inet.h>
  uint16_t htons(uint16_t hostshort)
  uint32_t htonl(uint32_t hostlong)
  uint32_t ntohl(uint32_t netlong)
  uint16_t ntohs(uint16_t netshort)
  These routines convert 16 and 32 bit quantities between NETWORK byte order and
  HOST byte order. Network byte order is big endian, or most significant byte first.
  On machines which have a byte order which is the same as the network byte order,
  routines are defined as null macros.
  These routines are most often used in conjunction with Internet addresses and
  ports as returned by gethostbyname()(for host) and getservent()(for ports). */
  name.sin_port = (in_port_t)htons(30000);

  /* Investigate the reserved port number by the OS.
  Macro: int IPPORT_RESERVED and int IPPORT_USERRESERVED are defined in <netinet/in.h>*/
  printf("Port numbers less than %i are reserved for superuser use.\n", IPPORT_RESERVED);
  printf("Port numbers greater than or equal to %i are reserved for explicit use; they will never be allocated automatically.\n", IPPORT_USERRESERVED);

  /* Rather than finding and using the machine's Internet address, this example
  specifies INADDR_ANY as the host address; the system replaces that with the
  machine's actual INTERNET address. */
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int reuse = 1; /* Use a non-zero value to enable the SO_REUSEADDR option. */
  /* getsockopt, setsockopt -- get and set options on sockets. <sys/socket.h>
  int getsockopt(int socket, int level, int option_name, void *restrict option_value,
                  socklen_t *restrict option_len);

  int setsockopt(int socket, int level, int option_name, const void *option_value,
                  socklen_t option_len);

  getsockopt() and setsockopt() manipulate the options associated with a socket.
  Options may exist at multiple protocol levels; they are always PRESENT at
  the UPPERMOST 'socket' level.
  When manipulating socket options the level at which the option resides and the
  name of the option must be specified. To manipulate options at the socket level,
  'level' argument is specified as SOL_SOCKET. To manipulate options at any other
  level the protocol number of the appropriate protocol controlling the option
  is supplied. For example, to indicate that an option is to be interpreted by the
  TCP protocol, 'level' argument should be set to the protocol number of TCP, use
  getprotoent() function.
  The parameters option_value and option_len are used to access option values for
  setsockopt(). For getsockopt() they specify a buffer in which the value for the
  requested option(s) are to be returned. For getsockopt(), option_len is a value-result
  parameter, initially containing the size of the buffer pointed to by option_value,
  and modified on return to indicate the actual size of the value returned. If no
  option value is to be supplied or returned, option_value may be NULL.
  'option_name' and any specified options are passed uninterpreted to the appropriate
  protocol module for interpretation. The include file <sys/socket.h> contains definitions
  for socket level options. Options at other protocol levels vary in format and
  name.
  Most socket-level options utilize an int parameter for option_value. For setsockopt(),
  the parameter should be non-zero to enable a boolean option, or zero if the option
  is to be disabled. SO_LINGER uses a struct linger parameter, defined in <sys/socket.h>,
  which specifies the desired state of the option and the linger interval. SO_SNDTIMEO
  and SO_RCVTIMEO use a struct timeval parameter, defined in <sys/time.h>.

  SO_REUSEADDR indicates that the rules used in validating addresses supplied in
  a bind() call should allow reuse of local addresses.
  SO_REUSEPORT allows completely duplicate bindings by multiple processes if they all set
  SO_REUSEPORT before binding the port. This option permits multiple instances of
  a program to each receive UDP/IP multicast or broadcast datagrams destined for
  the bound port.

  Upon successful completion, the value 0 is returned; otherwise the value -1 is
  returned and the global errno is set to indicate the error. */
  if(setsockopt(listener_desc, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
    error("Can't set the resue option on the socket");
  }

  /* int bind(int socket, struct sockaddr *addr, socklen_t length)
  The bind function assigns an ADDRESS TO the socket 'socket'.
  The 'addr' and 'length' arguments specify the address, the detailed format of
  the address depends on the namespace. The first part of the address is always
  the format designator, which specifies a namespace, and says that the address
  is in the format of that namespace.
  The return value is 0 on success and -1 on failure.

  manual on mac termial:
  bind -- bind a name to a socket. <sys/socket.h>
  int bind(int socket, const struct sockaddr *address, socklen_t address_len);

  bind() assigns a name to an UNNAMED socket. When a socket is created with socket()
  it exists in a name space (address family/protocol family) but has no name
  assigned. bind() requests that 'address' be assigned to 'socket'.

  Binding a name in the UNIX (aka. LOCAL) domain creates a socket in the file
  system that must be deleted by the caller when it is no longer needed (using unlink()).

  The RULEs used in name binding vary between communication domains. */
  int c = bind(listener_desc, (struct sockaddr *) &name, sizeof(name));
  if(c == -1){
    error("Can't bind to socket");
  }

  /* listen for connections on a socket, <sys/socket.h>
  Creation of socket-based connections requires several operations. First, a socket
  is created with socket() fucntion. Next, a willingness to accept incoming
  connections and a queue limit for incoming connections are specified with listen().
  Finally, the connections are accepted with accept() function. The listen() call
  applies only to sockets of type SOCK_STREAM.

  int listen(int socket, int backlog);
  The 'backlog' parameter defines the maximum length for the queue of pending connections.
  If a connection request arrives with the queue full, the client may receive an
  error with an indication of ECONNREFUSED. Alternatively, if the underlying protocol
  supports retransmission, the request may be ignored so that retries may succeed.

  The listen() function returns the value 0 if successful; otherwise the value -1
  is returned and the global variable errno is set to indicate the error. */
  if(listen(listener_desc, 10) == -1){
    error("Can't listen");
  }

  puts("Waiting for connection");

  /* The sockaddr_storage structure stores socket address information. Since the
  sockaddr_storage structure is sufficiently large to store address information
  for IPv4, IPv6, or other address families, its use promotes protocol-family and
  protocol-version independence and simplifies cross-platform development. Use the
  sockaddr_storage in place of the sockaddr structure. Doc from msdn.microsoft.com. */
  struct sockaddr_storage client_addr;
  unsigned int address_length = sizeof(client_addr);
  /* accept(): accept a connection on a socket. <sys/socket.h>

  int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);

  The 'argument' socket is a socket that has been created with socket(), bound to
  an address with bind(), and is listening for connections after a listen().
  accept() extracts the first connection request on the queue of pending connections,
  creates a new socket with the same properties of 'socket', and allocates a new
  file descriptor for the socket. If no pending connection are present on the queue,
  and the socket is not marked as non-blocking, accept() blocks the caller until
  a connection is present. If the socket is marked non-blocking and no pending
  connections are present on the queue, accept() returns an error as described below.
  The accepted socket may not be used to accept more connections. The original socket
  'socket' remains open.

  The argument 'address' is a result parameter that is filled in with the address
  of the connecting entity, as known to the communications layer. The exact format
  of the 'address' parameter is determined by the domain in which the communication
  is occuring. The 'address_len' is a value-result parameter; it should initially
  contain the amount of space pointed to by 'address'; on return it will contain
  the actual length (in bytes) of the address returned.

  This call is used with connection-based socket types, currently with SOCK_STREAM.

  The call returns -1 on error and the global variable errno is set to indicate
  the error. If it succeeds, it returns a non-negative integer that is a descriptor
  for the accepted socket. */
  char incoming_msg[128];
  while(1){
    int connect_desc = accept(listener_desc, (struct sockaddr*)&client_addr, &address_length);
    if(connect_desc == -1){
      error("Can't accept incoming connection request");
    }

    /* Note the length 127, we need take consideration of the terminating NUL character. */

    if(say(connect_desc, "Knock! Knock!\r\n") != -1){
      /* Check what the client say. */
      read_in(connect_desc, incoming_msg, sizeof(incoming_msg));
      printf("Incoming Msg: %s", incoming_msg);
      if(strncasecmp(incoming_msg, "Who's there?", 12) == 0){
        if(say(connect_desc, "Oscar!\r\n") != -1){
          read_in(connect_desc, incoming_msg, sizeof(incoming_msg));
          printf("Incoming Msg: %s", incoming_msg);
          if(strncasecmp(incoming_msg, "Oscar who?", 10) == 0){
            say(connect_desc, "Oscar silly question, you get a silly answer\r\n");
          }else{
            say(connect_desc, "You should say what's on the scripts!\r\n");
          }
        }
      }else{
        say(connect_desc, "You should say what's on the scripts!\r\n");
      }

      close(connect_desc);
    }

  }

  /* close -- delete a descriptor. <unistd.h>

  int close(int filedes);
  The close() call deletes a descriptor from the per-process object reference table.
  If this is the last reference to the underlying object, the object will be deactivated.
  For example, on the last close of a file the current seek pointer associated with the file
  is lost; on the last close of a socket associated naming information and queued
  data are discarded; on the last close of a file holding an advisory lock the
  lock is released.
  When a process exits, all associated file descriptors are freed, but since there
  is a limit on ACTIVE descriptors per process, the close() funciton call is
  useful when a large quantity of file descriptors are being handled.
  When a process forks, all descriptors for the new child process reference the
  same objects as they did in the parent before the the fork. If a new process
  is then to be run execve(), the process would normally inherit these descriptors.
  Most of the descriptors can be rearranged with dup2() or deleted with close()
  before the execve() is attempted, but if some of these descriptors will still be
  needed if the execve() fails, it is necessary to arrange for them to be closed
  if the execve() succeeds. For this reason, the call 'fcntl(d, F_SETFD, 1)' is
  proviced, which arranges that a descriptor will be closed after a successful
  execve(); the call 'fcntl(d, F_SETFD, 0)' restores the default, which is to not
  close the descriptor.

  Upon successful completion, a value of 0 is returned. Otherwise, a value of -1
  is returned.*/
  close(listener_desc);

  return 0;
}
