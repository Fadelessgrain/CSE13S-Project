#include "universe.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "tsn:i:o:"

#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000

int main(int argc, char **argv) {
    int rows;
    int cols;
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int generation = 100;

    bool toroidal = true;
    fscanf(infile, "%d %d\n", &rows, &cols);

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

    initscr();
    curs_set(FALSE);

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
    for (int i = 1; i < generation; i++) {
        clear();
        refresh();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                count = uv_census(a, r, c);
                if (count == 2 || count == 3) {
                    uv_live_cell(b, r, c);
                    if (r_s == true) {
                        mvprintw(r, c, "o");
                        usleep(DELAY);
                    }
                }
                bool x = uv_get_cell(a, r, c);
                if (x == false && count == 3) {
                    uv_live_cell(b, r, c);
                    if (r_s == true) {
                        mvprintw(r, c, "o");
                        usleep(DELAY);
                    }
                }
                if (count < 2) {
                    uv_dead_cell(b, r, c);
                    if (r_s == true) {
                        mvprintw(r, c, ".");
                        usleep(DELAY);
                    }
                }
                count = 0;
            }
        }
    }
    Universe *temp = b;
    a = b;
    b = temp;
    endwin();
    uv_print(a, outfile);
    uv_delete(a);
    uv_delete(b);
}
