# Assignment 4

This program takes in files, that come with certain specified permissions, and
encodes them, or decodes the files. This program has a generator file that
generates hamming codes for messages you want to encode. This program also 
includes a decoder file that decodes and corrects any errors in the codes 
that might have gotten damaged as well as keeps tracks of how many codes were
decoded, resolved, or even unresolved. 


## BUILD
	$ make: builds all the programs 
	$ make all: build ass the programs 
	$ make gen: creates the generator file
	$ make dec: creates the decoder files
	$ make err: creates the error file


## Running 
	$ ./gen -i -o : runs the generator code and takes in files as 
	input(i) and outputs them the specified (o) files.
	$ ./dec -i -o : runs the decoder code and takes in files as
     input(i) and outputs them the specified (o) files. 
	$ ./err -e -s : takes in error correcting ratio as input as well as the 
	speed to correct the errors/

## Clean
	$rm -f gen dec err *.o
