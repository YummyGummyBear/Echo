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
int validate_port (char *user_garbage)
{
	long int long_integer=0;
	char *character_pointer;
	int control = 1;
	int control2 = 0;
	errno = 0;


		while(control == 1) //Loops until user enters a valid positive whole number
		{
			
			if(strlen(user_garbage)>6)  // Provided too much input the program gives you the boot
			{
				bad("Homie don't play that\nIf you can't play nice then you can't play at all\nhttps://www.youtube.com/watch?v=Si29ntX65VI");
				exit (0);			
			}


			if(user_garbage[strlen(user_garbage)-1] == '\n') // Removes the new line char and replaces it with 0
			{
				user_garbage[strlen(user_garbage)-1] = 0;				

			}		
			errno=0;
			long_integer = strtol(user_garbage, &character_pointer, 0);  // Sorts array up to 0. Numbers into user_garbage and chars to character_pointer

			if(errno != 0 || *character_pointer != '\0')	// checks for errors and characters
			{
				bad("Not a valid port number"); 
				control2 = 1;				
			}
			if(long_integer<0 || long_integer>65535)  // Checks for range. Many Linux kernels use the port range 32768 to 61000.
			{
				bad("Not a valid port number"); 
				control2 = 1;				
			}
	
			else if (long_integer<65000 && long_integer>0)  // If all is good we are done
			{
				control = 0;
				control2 = 0;
			}
			if(control2 == 1)	// Gives user another chance to provide input
			{
				memset(user_garbage, 0, 100);
				printf("Please make a valid selection\n");
				fgets(user_garbage, 100, stdin);		
			}
	
		}



return (long_integer);
}

int bad(char *juju)
{
	fprintf(stderr,"%s\n", juju);  
	exit(0);	// This is almost the same as return 0. I can explain more in person.
}

#endif