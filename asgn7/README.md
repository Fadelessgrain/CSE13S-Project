# Assignment 7

This program had two main components. One of the first components includes encoding data. The 
encoding section of this assignment takes in files as inputs (or takes in inputs from stdin)
and encodes that data using bit manipulation and bit buffering. That encoded data can then 
be speicified to be outputed to the stdout or to a specific file. The second component of this lab
deals with decoding encoded data. During the decoding process, a file (or stdin) is taken as input
and is then decoded using bit buffering and bit manipulation, and outputed to stdout or a specified 
file. Both the deocing and encoding process collects stats that let the user know the size of the 
compressed files, the size of the uncompressed files, and how much space was saved. 

## BUILD
	$ make : builds both encoding and decoding programs
	$ make all : build both encoding and decoding programs
	$ make format: formats both .h and .c files to clang-format
	$ make clean: removes the binaries used to run the program
	$ make valgrind: checked for memory leaks in decode

# RUNNING 
	$ ./encode -i -o -v : takes in the option to encode file(i) and where to write the encoded 
	files to (o) and -v activates the stats for encoing / decoing.
	$./decoding -i -o -v : takes in the option to decode file(i) and where to write the decoded
  	files to (o) and -v activates the stats for encoing / decoing.  

## CLEAN
	$ rm -f encode decode *.o
