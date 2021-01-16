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
            int loser;
            loser = lives[0];
            for (int i = 1; 8 > i; i += 1) { //loop as long as there are players around
                printf("Round %d\n", i); // prints the rounds
                for (int s = 0; s < players; s += 1) { // loops through the players
                    if (lives[s] == 0) {
                        alive -= 1;
                        printf("%d", alive);
                        //    if (lives[s] != 0) { // only players with more than 0 lives can roll
                    } else {
                        printf(
                            " - %s rolls %s\n", names[s], rolls[roll()][roll()]); //prints the roll
                        if (loser > lives[s]) { // checks to find a lower min
                            loser = lives[s]; // if it finds a lower min, make that my new min
                            printf("%s is forced to eat garlic!", names[loser]);
                            lives[loser] -= 1; //subtracts the lives of the loser
                            if (lives[loser] == 1) { // one life for style purpose
                                printf("%s has %u life remaining.\n", names[loser], lives[loser]);
                            } else { //multiple lives for style purpose
                                printf("%s has %u lives remaining.\n", names[loser], lives[loser]);
                            }
                        }
                    }
                }
            }
        }
    }
}
