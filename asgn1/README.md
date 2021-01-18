# Assignment 1

This programs takes in two inputs from the user. The user inputs a valid number of players 
between 2-10 that play the Garlic games as well as valid seed. After accepting correct inputs
from the user, the players in the game start rolling dices to see who gets the highest rolled
dice. Whoever rolls the least, they have to eat the garlic and lose a life. If the 
player rolls a Midnight, also known as two 5s, then the players to the right and left of the
player who rolled get an extra life (ie sparkles) or gets resurrected. The game ends when there 
is only one player left. 

## BUILD 

	$ clang -Wall -Wextra -Werror -Wpedantic -o vampire vampire.c 

## Running 
	$ ./vampire

## Cleaning 
	$ rm -f vampire vamire.o 
