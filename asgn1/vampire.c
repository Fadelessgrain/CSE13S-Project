#include "names.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int roll(void) {
	return rand() % 6;
 }

int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
int main(void) {
	int players = 0;
	printf("Number of players: ");
	scanf("%d" , &players); 
	if (players < 2 || players > 10) { 
		fprintf(stderr, "Invalid number of players.\n");
		exit(1);
	}
	else {
	  int64_t seed = 0;     
	  printf("Random seed: ");
	  if (scanf("%" SCNd64, &seed) != 1 || seed < 0){  
	  	fprintf(stderr, "Invalid random seed\n");    
	  }
	  if (seed > UINT32_MAX){  
	  	fprintf(stderr, "Invalid random seed\n");                   
       	exit(1);    
	  }else{
//	for ( int i = 1; i < 10 ; i += 1) {
		for (int i = 1; i < lives[i]; i +=1) {
		printf("Round %d\n", i);
		srand(seed);
		for (int s = 0; s < players; s+= 1){
			int r = roll();
			printf(" - %s rolls %s\n",names[s], rolls[r][r]);
	
}
}
	}
	return 0;
}
}

