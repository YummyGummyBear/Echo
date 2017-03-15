CC=gcc				# Command to compile the files
RM=rm				# Command to delete files

server: jayLib.o server.o
	$(CC) $^ -o $@

jayLib.o: jayLib.c
	$(CC) -c -o $@ $<	

server.o: server.c
	$(CC) -c -o $@ $<

clean:
	$(RM) -f *.o
	$(RM) -f server
