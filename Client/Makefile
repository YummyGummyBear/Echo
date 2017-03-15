CC=gcc				# Command to compile the files
RM=rm				# Command to delete files

client: jayLib.o client.o
	$(CC) $^ -o $@

jayLib.o: jayLib.c
	$(CC) -c -o $@ $<		

client.o: client.c
	$(CC) -c -o $@ $<

clean:
	$(RM) -f *.o
	$(RM) -f client