#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
int roll(void) {
    return rand() % 6;
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
            srand(seed); //sets the seed
            for (int i = 1; lives[i] != 0; i += 1) { //loop as long as there are lives < counter
                printf("Round %d\n", i); // prints the rounds
                for (int s = 0; s < players; s += 1) { // loops through the players
                    if (lives[s] != 0) { // only players with more than 0 lives can roll
                        printf(
                            " - %s rolls %s\n", names[s], rolls[roll()][roll()]); //prints the roll
                        //	for (int t = 0; t < 10; t += 1) {
                        int loser = 0; // tracks the min roll
                        loser = lives[0]; // sets the min roll to 0
                        if (loser > lives[i]) { // checks to find a lower min
                            loser = lives[i]; // if it finds a lower min, make that my new min
                            printf("%s is forced to eat garlic!", names[loser]);
                            lives[loser] -= 1;
                            if (lives[loser] == 1) {
                                printf("%s has %u life remaining.\n", names[loser], lives[loser]);
                            } else {
                                printf("%s has %u lives remaining.\n", names[loser], lives[loser]);
                            }
                        }
                    }
                }
            }
            return 0;
        }
    }
}
