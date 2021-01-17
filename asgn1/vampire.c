#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t left(uint32_t pos, uint32_t players) {
    return (pos + players - 1) % players;
}

uint32_t right(uint32_t pos, uint32_t players) {
    return (pos + 1) % players;
}
//Code below from Eugene's secion
int roll(void) {
    return random() % 6;
}
//Code above from Eugenue's section
int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; // creates lives

int main(void) {
    int players = 0;
    printf("Number of players: ");
    scanf("%d", &players);
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players.");
        exit(1);
    } else {
        // code below from Eugene's section
        int64_t seed = 0;
        printf("Random seed: ");
        if (scanf("%" SCNd64, &seed) != 1 || seed < 0) {
            fprintf(stderr, "Invalid random seed.");
            exit(1);
        }
        if (seed > UINT32_MAX) {
            fprintf(stderr, "Invalid random of seed.");
            exit(1);
            // code above from Eugene's section
        } else {
            srandom(seed);
            int alive = players;
            int loser = 13;
            int rounds = 1;
            int index = 0;
            int l = 0;
            int winner = 0;
            int w = 0;
            int r = 0;
            int L = 0;
            while (alive > 1) {
                printf("Round %d\n", rounds);
                for (int s = 0; s != players; s += 1) {
                    if (lives[s] != 0) {
                        int r1 = roll();
                        int r2 = roll();
                        int r3 = r1 + r2;
                        if (rolls[r1][r2] == rolls[5][5]) {
                            r = right(s, players);
                            L = left(s, players);
                            lives[L] += 1;
                            lives[r] += 1;
                            if (lives[L] == 1) {
                                alive += 1;
                                if (lives[r] == 1) {
                                    alive += 1;
                                    printf(" - %s rolls %s... resurrects %s resurrects %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                } else {
                                    printf(" - %s rolls %s... resurrects %s sparkles %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                }
                            }
                            if (lives[L] > 1) {
                                if (lives[r] > 1) {
                                    printf(" - %s rolls %s... sparkles %s sparkles %s\n", names[s],
                                        rolls[r1][r2], names[L], names[r]);
                                } else {
                                    alive += 1;
                                    printf(" - %s rolls %s... sparkles %s resurrects %s\n",
                                        names[s], rolls[r1][r2], names[L], names[r]);
                                }
                            }
                        } else {
                            printf(" - %s rolls %s...\n", names[s], rolls[r1][r2]);
                        }
                        if (r3 < loser) {
                            loser = r3;
                            index = s;
                            l = s;
                        }
                        if (r3 > winner) {
                            winner = r3;
                            w = s;
                        }
                    }
                    if (s + 1 == players) {
                        lives[l] -= 1;
                        printf("%s is forced to eat garlic!\n", names[index]);
                        loser = 13;
                        winner = 0;
                        if (lives[l] == 1) {
                            printf("%s has %d life remaining.\n", names[index], lives[l]);
                        } else {
                            if (lives[l] == 0) {
                                alive -= 1;
                                printf("%s has died.\n", names[index]);
                            } else {
                                printf("%s has %d lives remaining.\n", names[index], lives[l]);
                            }
                        }
                        if (alive == 1) {
                            printf("%s wins the Garlic Game!\n", names[w]);
                        }
                        rounds += 1;
                    }
                }
            }
        }
    }
}
