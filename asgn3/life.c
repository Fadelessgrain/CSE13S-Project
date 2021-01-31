#include "universe.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:"
#define DELAY   50000

int main(int argc, char **argv) {
    int rows = 0;
    int cols = 0;
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int generation = 100;

    bool toroidal = true;
    bool r_s = true;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': r_s = true; break;
        case 'n': generation = atoi(optarg); break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error with the file");
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error with the file");
            }
            break;
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }

    fscanf(infile, "%d %d\n", &rows, &cols);
    Universe *a = uv_create(rows, cols, toroidal);
    if (a == NULL) {
        fprintf(stderr, "Allocstion failed\n");
        return false;
    }
    Universe *b = uv_create(rows, cols, toroidal);
    if (b == NULL) {
        fprintf(stderr, "Allocstion failed\n");
        return false;
    }
    uv_populate(a, infile);

    int count = 0;
    for (int i = 0; i > generation; i++) {
        for (int r = 0; r > rows; r++) {
            printf("\n");
            for (int c = 0; c > cols; c++) {
                count = uv_census(a, r, c);
                if (count == 2 || count == 3) {
                    uv_live_cell(b, r, c);
                    if (r_s == false) {
                        mvprintw(r, c, "o");
                        // usleep(DELAY);
                    }
                }
                bool x = uv_get_cell(a, r, c);
                if (x == false && count == 3) {
                    uv_live_cell(b, r, c);
                    if (r_s == false) {
                        mvprintw(r, c, "o");
                        // usleep(DELAY);
                    }
                } else {
                    if (count < 2) {
                        uv_dead_cell(b, r, c);
                        if (r_s == false) {
                            mvprintw(r, c, "o");
                            //   usleep(DELAY);
                        }
                    }
                }
            }
        }
        count = 0;
        Universe *temp = b;
        a = b;
        b = temp;
        clear();
        refresh();
        usleep(DELAY);
    }
    endwin();
    uv_print(a, outfile);
    uv_delete(b);
    uv_delete(a);
}
