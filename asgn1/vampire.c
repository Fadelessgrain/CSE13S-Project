#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int roll(void) {
    return random() % 6;
}

int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; // creates lives
int main(void) {
    int players = 0;
    printf("Number of players: "); // number of players
    scanf("%d", &players);
    if (players < 2 || players > 10) { // checks for valid input
        fprintf(stderr, "Invalid number of players.\n");
        exit(1);
    } else {
        int64_t seed = 0;
        printf("Random seed: "); //asks for seed
        if (scanf("%" SCNd64, &seed) != 1 || seed < 0) { //checks for valid input
            fprintf(stderr, "Invalid random seed\n");
            exit(1);
        }
        if (seed > UINT32_MAX) { //checks for valid input
            fprintf(stderr, "Invalid random seed\n");
            exit(1);
        } else {

            srandom(seed); //sets the seed
            int alive = players;
            printf("%d", alive);
      		int loser = 13;
			int rounds = 1;
			int index = 0;
			while (rounds < 8){
			printf("Round %d\n", rounds);
			for (int s = 0; s != players; s+=1) {
				int r1 = roll();
				int r2 = roll();
				int r3 = r1 + r2;
				printf(" - %s rolls %s... %d\n",names[s], rolls[r1][r2], r3); 
				if (r3 < loser) {
					loser = r3;
					index = s;
				}
			rounds += 1;
			if (s+1 == players) {
				printf("The min: %d\n", loser);
				printf("%s is forced to eat garlic!", names[index]);
				loser = 13;
			}

    }
}
}
}
}
