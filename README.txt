README

I didn't feel like writing a Makefile soooo....

Copy and paste:

gcc -o server validate_port.c bad.c server.c 
gcc -o client validate_port.c bad.c client.c

How to use:

./server <PORT> <IP_ADDRESS>
./client <HOSTNAME> <PORT>