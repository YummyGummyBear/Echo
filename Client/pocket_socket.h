#ifndef POCKET_SOCKET_H_
#define POCKET_SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // memset
#include <sys/types.h>  // data types used in system calls
#include <sys/socket.h> // structs needed for sockets
#include <netinet/in.h> // constants and structs needed for internet domain addresses
#include <netdb.h>  	// definitions for network database operations 
#include <unistd.h>  	// standard symbolic constants and types Portable Operating System Interface (POSIX)
#include <arpa/inet.h>	// definitions for internet operations
#include <ctype.h>	// functions to test and map characters
#include <errno.h>	//  used for error handling

int bad(char *juju);
int validate_port (char *user_garbage);

#endif