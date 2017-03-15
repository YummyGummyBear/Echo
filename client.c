/* Jayson Bennett */

/* Link section */

#include "pocket_socket.h"  // Puppies and kittens
int validate_port (char *user_garbage);
int bad(char *juju);
/* A simple client that connects to a server using hostname and port provided via command line args. */


int main(int argc, char *argv[])
{
	int socket_file_descriptor=0;
	int port_number=0;
	int number_of_bytes=0;
	struct sockaddr_in server_address;
	struct hostent *server;
	char client_buffer[65535];
	char str[INET_ADDRSTRLEN];
	if (argc < 3) 
	{
		bad("\nToo few arguments\n\n\t\t\tUsage: ./client <Host Name> <Server Port>\n");
	}
	if (argc > 3) 
	{
		bad("\nToo many arguments\n\n\t\t\tUsage: ./client <Host Name> <Server Port>\n");
	}

	port_number = validate_port(argv[2]);

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_file_descriptor < 0)
	{ 
		bad("\nUnable to open socket\n");
	}

	server = gethostbyname(argv[1]);

	if (server == NULL) 
	{
		bad("\nUnknown host\n");
	}

	memset((char *) &server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
	server_address.sin_port = htons(port_number);
	if (connect(socket_file_descriptor,(struct sockaddr *)&server_address,sizeof(server_address)) < 0) 
	{
		bad("\nUnable to connect\n");
	}
	inet_ntop(AF_INET, &(server_address.sin_addr), str, INET_ADDRSTRLEN);

	printf("\nYou are connected!\nServer: %s\nIP:     %s\nPort:   %s\n\n", argv[1], str, argv[2]);

	for(int i=15; i>0; i--) // Stops after 15 messages
	{
		memset(client_buffer, 0, 65535);
		printf("\nSENDING: ");
		fgets(client_buffer,65535,stdin);
	
		number_of_bytes = write(socket_file_descriptor,client_buffer,strlen(client_buffer));

		if (number_of_bytes < 0)
		{ 
			bad("\nAn error occurred writing to socket\n");
		}

		memset(client_buffer, 0, 65535);
		number_of_bytes = read(socket_file_descriptor,client_buffer,65535);
		if (number_of_bytes < 0) 
		{
			bad("ERROR reading from socket");
		}
		printf("\nRECEIVING: %s\n", client_buffer);
		
	}
	close(socket_file_descriptor);		// Closes file descriptor breaking the while loop in the server.c
return 0;
}