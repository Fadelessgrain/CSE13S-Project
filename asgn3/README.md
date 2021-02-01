# Assignment 3
This program mimics the game of life. Based on certain arguments parsed in the command line, 
our universe will progress through generations based on the state of the cells. If the cell we 
are examining is currently alive and it has three or two neighbors, the cell survives. If a dead
cell has three live neighbors, the cell becomes alive. Otherwise, the cell dies. The valid
commands that can be parsed to the command life are -t, -s, -n, -i, and -o. The command -t 
makes it to that the game of life will be played in a toroidal universe and not a flat earth.
The command -s will silence the ncurser and it will not display it on the screen.
The comman -n sets the number of generations to be played. If the user does not include a -n 
command, the defult will be 100. The command -i specifies what file we will be reading from. If 
this command is not passed, the defult will be stdin.
The command -o specifies what file we will be writting and printing to. If this command is not
parse, the defult will be stdout.

## BUILD 
	$ clang -Wall -Werror -Wextra -Wpedantic   -c life.c
	$ clang -Wall -Werror -Wextra -Wpedantic   -c universe.c 
	$ clang -o life life.o universe.o -lncurses
	$ make all 

## Running 
	$./life -t -s -n -i -o.

## Cleaning 
	$ rm -f life *.o
