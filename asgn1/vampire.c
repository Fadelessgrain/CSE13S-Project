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
    printf("Number of players: ");
    scanf("%d", &players);
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid Number of players.");
        exit(1);
    } else {
        int64_t seed = 0;
        printf("Random seed: ");
        if (scanf("%" SCNd64, &seed) != 1 || seed < 0) {
            fprintf(stderr, "Invalid Number of seeds.");
            exit(1);
        }
        if (seed > UINT32_MAX) {
            fprintf(stderr, "Invalid Number of seeds.");
            exit(1);
        } else {
            srandom(seed);
            int alive = players;
            int loser = 13;
            int rounds = 1;
            int index = 0;
            int l = 0;
            while (alive > 1) {
                printf("Round %d\n", rounds);
                for (int s = 0; s != players; s += 1) {
                    if (lives[s] > 0) {
                        int r1 = roll();
                        int r2 = roll();
                        int r3 = r1 + r2;
                        printf(" - %s rolls %s\n", names[s], rolls[r1][r1]);
                        if (r3 < loser) {
                            loser = r3;
                            index = s;
                            l = s;
                        }
                    }
                    if (s + 1 == players) {
                        lives[l] -= 1;
                        printf("%s is forced to eat garlic!\n", names[index]);
                        loser = 13;
                        printf("%s has %d life.\n", names[index], lives[l]);
                    }
                    if (lives[index] == 0) {
                        alive -= 1;
                        printf("%s has died\n", names[index]);
                    }
                    rounds += 1;
                }
            }
        }
    }
}
//}
