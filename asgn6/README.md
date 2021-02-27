# Assignment 6

This program takes in words from stdin and checls to see if they are valid words. If they are not
valid words, they should be added to a linked list and the user will recieve a message will
their crimes, and suggestions on how to speak goodspeak. 

## BUILD 
	$ make : builds the banhammer program
	$ make all: builds the banhammer program
	$ make clean: removes the binaries used to run the program
	$ make format: formats the .h and .c files into clang format
	$ make valgrind: runs valgrind anc checks for memory leeks

## RUNNING 
	$ ./banhammer -m -h -f -m : takes in the optiont of changing the hash table's size 
	or the bloom filter's size, or we can activate the move to the front option
	$ cat ./badspeak.txt ./newspeak.txt | ./banhammer

##CLEAN
	$ rm -f banhammer *.o
