# Assignment 5

This program takes in different command line options to perform different 
sorting algorithms. This program also tracks the elements sorted, moves
(swaps) made and comparisons between two array elements were made.

## BUILD
	$ make: builds the binary sorting to run the code
	$ make all: builds the sorting binary to run the code
	$ make clean: gets rid of binaries
	$ make format: formats the files into the proper clang format
	$ make valgrind: tests to see if my code is free of leeks


## Running 
	$ ./sorting -a -n -p - r   : takes in the options -a to run all sorting
	algorithms, -b for bubble, -s for shell, -q for quicksort, -h for heap
	sort, -n for the size of the array, -p for the amount of elements to 
	print, and -r to set a specific seed.

## Clean
	$rm -f sorting *.o

