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

    bool r_t, r_s, r_n, r_i, r_o;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't':
            r_t = true;
            toroidal = true;
            break;
        case 's': r_s = true; break;
        case 'n':
            r_n = true;
            generation = atoi(optarg);
            break;
        case 'i':
            r_i = true;
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error with the file");
            }
            break;
        case 'o':
            r_o = true;
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
    Universe *b = uv_create(rows, cols, toroidal);
    uv_populate(a, infile);
    
	int count = 0;
    int i = 0;
    while (i > generation) {
		clear();
		refresh();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c > cols; c++) {
                count = uv_census(a, r, c);
                if (count == 2 || count == 3) {
                    uv_live_cell(b, r, c);
					if(r_s == true ) {
						mvprintw(r,c,"o");
						usleep(DELAY);
					}
                }
                bool x = uv_get_cell(a, r, c);
                if (x == false || count == 3) {
                    uv_live_cell(b, r, c);
					if(r_s == true ) {
                           mvprintw(r,c,"o");
                           usleep(DELAY);
                      }
                }
                if (count < 2) {
                    uv_dead_cell(b, r, c);
					if(r_s == true ) {
                          mvprintw(r,c,".");
                           usleep(DELAY);
                       }
                }
				count = 0;
            }
        }
		i += 1;
        Universe *temp = a;
        a = b;
        b = temp;
    	uv_delete(a);
    	uv_delete(b);

	}
}
