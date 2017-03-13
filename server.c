/* Jayson Bennett */

/* Link section */

#include "pocket_socket.h"	// Rickety Rickety Wrecked

/* Simple server, starts with user provided port # and IP */


int main(int argc, char *argv[])
{
	int socket_file_descriptor=0, accept_file_descriptor=0;  // initializing variables for file descriptors
	int port_number=0, length_of_client_address=0, number_of_bytes=0;  // port number, client address length, bytes to be read/write
	char buffer[256];
	struct sockaddr_in server_address, client_address;  // creating 2 structs of the sockaddr_in type defined in netinet/in.h
	memset(buffer, 0, 256);		// Filling buffer with zeros
	errno =0;					// Clearing errno...which I'm going to use later for the chat comp
	char str[INET_ADDRSTRLEN];
	memset((char*) &server_address, 0, sizeof(server_address));
		
	if (argc < 3)    // Checking for correct number of args
	{
		bad("Too few arguments\n\tUsage: ./server <Port> <IP Address>");
	}
	if (argc > 3) 
	{
		bad("Too many arguments\n\tUsage: ./server <Port> <IP Address>");
	}
	
	if(inet_pton(AF_INET, argv[2], &(server_address.sin_addr)) == 0)    // Validating IP
	{
		bad("Invalid IP\n\tUsage: ./server <Port> <IP Address>");
	}

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);  // Address family internet (domain), Stream=TCP, 0 tells the OS to choose the appropriate protocol
	if (socket_file_descriptor < 0)  // If socket call fails -1 is returned
	{
		bad("Unable to open socket");
	}
	memset((char *) &server_address, 0, sizeof(server_address));  // writing zeros to memory space allocated to server_address
	port_number = validate_port(argv[1]);		// Validating port
	server_address.sin_family = AF_INET;		// This declares the address family to be IPv4
	server_address.sin_port = htons(port_number);	// htons=host to network bits aka Big Native American

	if (bind(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) 
	{
		bad("ERROR on binding");
	}

	/* 5 is the number of connections that can be waiting while the process is handling a particular connection. 5 is the maximum size permitted by most systems */
	listen(socket_file_descriptor,5);

	printf("Listening to you\nI get the music\n\n");    // The Who
	length_of_client_address = sizeof(client_address);
	accept_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *) &client_address, &length_of_client_address);

	if (accept_file_descriptor < 0) 
	{
		bad("ERROR on accept");
	}
	int i=1;
	while(i=1)	// Runs forever or until ctrl-c is received from client or the connection is closed
	{
		
		memset(buffer, 0, 256);
		number_of_bytes = read(accept_file_descriptor,buffer,255);

		if (number_of_bytes < 0) 
		{
			bad("ERROR reading from socket");
		}


		printf("RECEIVING: %s\n",buffer);
//		number_of_bytes = write(accept_file_descriptor,"I got your message",18);
		number_of_bytes = write(accept_file_descriptor,buffer,255);
		if (number_of_bytes < 0)
		{
			bad("ERROR writing to socket");
		}

	}

   	close(socket_file_descriptor);	// Does what is says :)

return 0; 
}
