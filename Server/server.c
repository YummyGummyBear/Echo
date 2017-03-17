/* Jayson Bennett */

/* Link section */

#include "pocket_socket.h"	// Rickety Rickety Wrecked
int validate_port (char *user_garbage);
int bad(char *juju);
/* Simple server, starts with user provided port # and IP */


int main(int argc, char *argv[])
{
	int socket_file_descriptor=0, accept_file_descriptor=0;  // initializing variables for file descriptors
	int port_number=0, length_of_client_address=0, number_of_bytes=0;  // port number, client address length, bytes to be read/write
	char server_buffer[4097];
	struct sockaddr_in server_address, client_address;  // creating 2 structs of the sockaddr_in type defined in netinet/in.h
	memset(server_buffer, 0, 4097);		// Filling server_buffer with zeros
	errno =0;					// Clearing errno...which I'm going to use later for the chat comp
	char str[INET_ADDRSTRLEN];
	memset((char*) &server_address, 0, sizeof(server_address));
		
	if (argc < 3)    // Checking for correct number of args
	{
		bad("Too few arguments\n\tUsage: ./server <IP Address> <Port>");
	}
	if (argc > 3) 
	{
		bad("Too many arguments\n\tUsage: ./server <IP Address> <Port>");
	}
	
	if(inet_pton(AF_INET, argv[1], &(server_address.sin_addr)) == 0)    // Validating IP
	{
		bad("Invalid IP\n\tUsage: ./server <IP Address> <Port>");
	}

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);  // Address family internet (domain), Stream=TCP, 0 tells the OS to choose the appropriate protocol
	if (socket_file_descriptor < 0)  // If socket call fails -1 is returned
	{
		bad("Unable to open socket");
	}
	memset((char *) &server_address, 0, sizeof(server_address));  // writing zeros to memory space allocated to server_address
	port_number = validate_port(argv[2]);		// Validating port
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
	
	while(1)    // Runs forever or until the connection is closed
	{
		
		memset(server_buffer, 0, 4097);
		number_of_bytes = read(accept_file_descriptor,server_buffer,4097);

		if (number_of_bytes < 0) 
		{
			bad("ERROR reading from socket");
		}
		if(number_of_bytes == 0)
		{
			printf("Connection has been closed\nGood bye\n");
			break;
		}
		printf("You have received %d bytes from a client\n", number_of_bytes);
		printf("\nData received: %s\n",server_buffer);
		printf("Sending %lu bytes to client\n\n", strlen(server_buffer));
		number_of_bytes = write(accept_file_descriptor,server_buffer, 4097);
		if (number_of_bytes < 0)
		{
			bad("ERROR writing to socket");
		}
		printf("Waiting for next transmission....\n\n");
		
	}

   	close(socket_file_descriptor);	// Does what is says :)

return 0; 
}
