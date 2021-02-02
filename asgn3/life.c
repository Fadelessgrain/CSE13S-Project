#include "universe.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//creates the command line opntions
#define OPTIONS "tsn:i:o:"
//sets the delay
#define DELAY 50000

int main(int argc, char **argv) {
    int opt = 0;
    //set the standard file
    FILE *infile = stdin;
    //set the standard file to print to
    FILE *outfile = stdout;
    //set the stanard geneation to 100
    int generation = 100;
    //init toroidal
    bool toroidal = true;
    bool r_s = true;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            //set toroidal to true
        case 't':
            toroidal = true;
            break;
            //sets the cursers to false
        case 's': r_s = false; break;
        case 'n':
            //sets the number of generations
            generation = atoi(optarg);
            //checks that it's a valud number of generation
            if (generation < 1) {
                fprintf(stderr, "Invalid number of generations");
                //if you give an invalid number of generations, set the defult to 100
                generation = 100;
            }
            break;
        case 'i':
            //sets the input file
            infile = fopen(optarg, "r");
            //if the input file is invalid, return an error
            if (infile == NULL) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        case 'o':
            //sets the outfile
            outfile = fopen(optarg, "w");
            //if the outfile is invalid, return an error
            if (outfile == NULL) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    //read the file
    int rows = 0;
    int cols = 0;
    fscanf(infile, "%d %d\n", &rows, &cols);
    //create universe a
    Universe *a = uv_create(rows, cols, toroidal);
    //create universe b
    Universe *b = uv_create(rows, cols, toroidal);
    uv_populate(a, infile);
    //counter that will be used to check the 3 conditions
    //to see if a cell is alive/dead
    int count = 0;
    //sets the screen for curses
    if (r_s == true) {
        initscr();
        noecho();
        curs_set(FALSE);
    }
    //generate through the generations
    for (int i = 0; i < generation; i += 1) {
        //generate through the rows
        for (int r = 0; r < rows; r += 1) {
            //igenerate through the cols
            for (int c = 0; c < cols; c += 1) {
                //print the ncurses
                if (r_s == true) {
                    clear();
                    if ((uv_get_cell(a, r, c) == true)) {
                        mvprintw(r, c, "o");
                        refresh();
                        usleep(DELAY);
                    }
                }
                //gets the number of neighboors
                count = uv_census(a, r, c);
                //gets the value of a cell
                bool x = uv_get_cell(a, r, c);
                if (x == true && (count == 2 || count == 3)) {
                    uv_live_cell(b, r, c);
                }
                //if there is a dead cell with three neighboors, make the cell alive
                if (x == false && count == 3) {
                    uv_live_cell(b, r, c);
                }

                if (count < 2 || count > 2) {
                    //kill the cell
                    uv_dead_cell(b, r, c);
                } else {
					uv_get_cell(b, r,c);
                //resets the counter for each generation
                }
				count = 0;
}
            Universe *temp = a;
            a = b;
            b = temp;
            endwin();
       
	   }
    }
    //return the curses
    curs_set(TRUE);
    //print universe a
    uv_print(a, outfile);
    //delete universe a
    uv_delete(a);
    //delete universe b
    uv_delete(b);
    //closes both files
    fclose(infile);
    fclose(outfile);
    return 0;
}
