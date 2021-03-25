#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//	calculates position of left player
uint32_t left(uint32_t pos, uint32_t players) {
    return (pos + players - 1) % players;
}
//  calculates position of right player/
uint32_t right(uint32_t pos, uint32_t players) {
    return (pos + 1) % players;
}
// makes sure we stay in our bounds
int roll(void) {
    return random() % 6;
}
int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; // creates lives

int main(void) {
    // checks for a valid number of players
    int players = 0;
    printf("Number of players: ");
    scanf("%d", &players);
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players.");
        exit(1);
    } else {
		// checks for a valid number of seed
        int64_t seed = 0;
        printf("Random seed: ");
        if (scanf("%" SCNd64, &seed) != 1 || seed < 0) {
            fprintf(stderr, "Invalid random seed.");
            exit(1);
        }
        if (seed > UINT32_MAX) {
            fprintf(stderr, "Invalid random of seed.");
            exit(1);
        } else {
            //if user inputs a valid seed, start the game
            srandom(seed);
            // alive tracks the players with lives > 0
            int alive = players;
            // loser tracks which player rolled the lowest roll
            int loser = 13;
            // rounds keeps tracks of the rounds
            int rounds = 1;
            // keeps track of the index of the loser
            int index_loser = 0;
            // keeps track of the person who needs to lose a live
            int lose_live = 0;
            // winner keeps track of the winner
            int winner = 0;
            // keeps track of the winners index
            int winner_index = 0;
            // keeps track of index of player in the right
            int r = 0;
            // keeps track of index of player in the left
            int L = 0;
            //loops as soon as there are more than one players alive
            while (alive > 1) {
                printf("Round %d\n", rounds);
                // iterates through the players playing the game
                for (int s = 0; s != players; s += 1) {
                    // if the current player has more than 0 lives, role
                    if (lives[s] != 0) {
                        // keeps track of first roll
                        int r1 = roll();
                        // keeps track of second roll
                        int r2 = roll();
                        // keeps track total number of roll
                        int roll_total = r1 + r2;
                        //	if player rolls a Midnight
                        if (rolls[r1][r2] == rolls[5][5]) {
                            r = right(s, players);
                            L = left(s, players);
                            //	increments the lives of left and right players
                            lives[L] += 1;
                            lives[r] += 1;
                            //	if the left player's life was 0 but was added 1,
                            //	increment the counter for players who are alive
                            // 	these if states are for formating purpose mostly
                            //  to make sure the correct thing is being printed out
                            if (lives[L] == 1) {
                                alive += 1;
                                // if the right player's life was also 0, but was added 1,
                                // increment the counter for players who are alive print
                                // 	recurrects
                                if (lives[r] == 1) {
                                    alive += 1;
                                    printf(" - %s rolls %s... resurrects %s resurrects %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                    //	if right player's life was not 0, then don't incrment alive
                                    //	counter and print sparkles
                                } else {
                                    printf(" - %s rolls %s... resurrects %s sparkles %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                }
                                //	if the left players was > 0, print sparkles not resurrects
                            }
                            if (lives[L] > 1) {
                                //	if right player was > 0, prints sparkles
                                if (lives[r] > 1) {
                                    printf(" - %s rolls %s... sparkles %s sparkles %s\n", names[s],
                                        rolls[r1][r2], names[L], names[r]);
                                    //	if right player was less than 1 (i.e was dead), print
                                    //	resurrects
                                } else {
                                    alive += 1;
                                    printf(" - %s rolls %s... sparkles %s resurrects %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                }
                            }
                            //	else if not Midnight, print regular format
                        } else {
                            printf(" - %s rolls %s...\n", names[s], rolls[r1][r2]);
                        }
                        // checks to find a min roll dice
                        if (roll_total < loser) {
                            // sets the 'new' lowest roll
                            loser = roll_total;
                            //	index keeps track of the player that made that roll to print
                            // 	loser
                            index_loser = s;
                            // l keeps track of the player that made made the roll to sub lives
                            lose_live = s;
                            // check to see who the user with the highest roll is
                        }
                        if (roll_total > winner) {
                            // winner sets the new 'high' roll
                            winner = roll_total;
                            // w keeps track of the index of the player who made the roll
                            winner_index = s;
                        }
                    }
                    // once my loop condition is met
                    if (s + 1 == players) {
                        // subtract 1 live from l (i.e the index of who made the role
                        lives[lose_live] -= 1;
                        printf("%s is forced to eat garlic!\n", names[index_loser]);
                        // resets the counter of lowest roll for a new round
                        loser = 13;
                        //	resets the counter of the highest roll for a new round
                        winner = 0;
                        //	if its one life, print a singular form of lifw
                        if (lives[lose_live] == 1) {
                            printf("%s has %d life remaining.\n", names[index_loser],
                                lives[lose_live]);
                        } else {
                            // if lives is 0, print they died
                            if (lives[lose_live] == 0) {
                                // subtract one from my players alive counter
                                alive -= 1;
                                printf("%s has died.\n", names[index_loser]);
                            } else {
                                // else print the plural form lives
                                printf("%s has %d lives remaining.\n", names[index_loser],
                                    lives[lose_live]);
                            }
                        } // if there is only one player left, print out winner
                        if (alive == 1) {
                            printf("%s wins the Garlic Game!\n", names[winner_index]);
                        }
                        // increment the round
                        rounds += 1;
                    }
                }
            }
        }
    }
}
