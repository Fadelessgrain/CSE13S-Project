#include "names.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; // creates lives
int main(void) {
	int players = 0;
	printf("Number of players: ");   // number of players 
	scanf("%d" , &players); 
	if (players < 2 || players > 10) { // checks for valid input
		fprintf(stderr, "Invalid number of players.\n");
		exit(1);
	}
	else {
	  int64_t seed = 0;     
	  printf("Random seed: "); //asks for seed 
	  if (scanf("%" SCNd64, &seed) != 1 || seed < 0){ //checks for valid input  
	  	fprintf(stderr, "Invalid random seed\n");    
	  	exit(1);
	  }
	  if (seed > UINT32_MAX){  //checks for valid input
	  	fprintf(stderr, "Invalid random seed\n");                   
       	exit(1);    
	  } else {
		for (int i = 1; i < lives[i]; i +=1) { //loop as long as there are lives < counter
			printf("Round %d\n", i); // prints the rounds
			for (int s = 0; s < players; s+= 1){ // loops through the players
				if (lives[s] != 0){ // only players with more than 0 lives can roll
					srand(seed); //sets the seed
					int r = rand() % 6; //random 
					printf(" - %s rolls %s\n",names[s], rolls[r][r]); //prints the roll
				int loser = 0; // tracks the min roll
				loser = lives[0]; // sets the min roll to 0
				if (lives[s] < loser) { // checks to find a lower min
					loser = lives[s];  // if it finds a lower min, make that my new min
					printf("%s is forced to eat garlic!", names[s]);
}
}
}
}
	return 0;
}
}
}

