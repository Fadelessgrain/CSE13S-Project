#include "universe.h"

#include <stdlib.h>
struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};
//allocates memory for the universes
Universe *uv_create(int rows, int cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    //if we are in an invalid pointer; return Null
    if (u == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return NULL;
    }
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    //allocate memory for the grid
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    //if we are in an invalid location, return n
    if (u == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return NULL;
    }
    // allocate memory for the value of the grid
    for (int i = 0; i < rows; i++) {
        u->grid[i] = (bool *) calloc(cols, sizeof(bool));
    }
    //return a universe
    return u;
}
//free the memory I allocated
void uv_delete(Universe *u) {
    //free the memory for the value of the grid
    for (int i = 0; i < u->rows; i++) {
        free(u->grid[i]);
    }
    //free the memeory of the grid
    free(u->grid);
    //free the universe
    free(u);
    return;
}
//returns the number of rows in a universe
int uv_rows(Universe *u) {
    return u->rows;
}
//returns the numbr of cols in a universe
int uv_cols(Universe *u) {
    return u->cols;
}
//if pointer or c are are >= the number of rows or cols and if pointer r or c <0,
//then it's out of bounce and return false, else return true
bool out_of_bounds(Universe *u, int r, int c) {
    if (r >= u->rows || r < 0 || c >= u->rows || c < 0) {
        return false;
    } else {
        return true;
    }
}
//if the pointer is in bounce, set the grid to true else nothing
void uv_live_cell(Universe *u, int r, int c) {
    bool x = out_of_bounds(u, r, c);
    if (x == true) {
        u->grid[r][c] = true;
        return;
    } else {
        return;
    }
}
//if the  pointer is in bounce, set the grid to false, else nothing
void uv_dead_cell(Universe *u, int r, int c) {
    bool x = out_of_bounds(u, r, c);
    if (x == true) {
        u->grid[r][c] = false;
        return;
    } else {
        return;
    }
}
//checks if a cell is dead/alive
bool uv_get_cell(Universe *u, int r, int c) {
    //check if the cell is in bound
    bool x = out_of_bounds(u, r, c);
    //check if we are in toroidal
    if (u->toroidal != false) {
        //if its out of bounce and the cell is dead, return false
        if (x == false || u->grid[r][c] == false) {
            return false;
        }
        //if its in bound and the cell is alive, return true
        if (x == true || u->grid[r][c] == true) {
            return true;
        }
        //if not in toroidal, return the value of the cell
    } else {
        return u->grid[r][c];
    }
    return u->grid[r][c];
}
//populate the universe
bool uv_populate(Universe *u, FILE *infile) {
    int row = 0;
    int colum = 0;
    //if the first file is scanned for the dimention
    bool dim = false;
    //scan the file until you reach the end
    while (fscanf(infile, "%d %d\n", &row, &colum) != EOF) {
        //we read the dimentions
        dim = true;
        //if it's out f bounce failed to populate
        int x = out_of_bounds(u, row, colum);
        if (x == false && dim == true) {
            return false;
            fprintf(stderr, "Failed to populate\n");
            //else populate the grid
        } else {
            u->grid[row][colum] = true;
        }
    }
    return true;
}
//counts the neighboors
int uv_census(Universe *u, int r, int c) {
    int neighboors = 0;
    //if not in toroidal, then don't do modulo and loop around (r,c)
    if (u->toroidal == false) {
        if (uv_get_cell(u, r - 1, c - 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r - 1, c) == true) {
            neighboors += 1;
            printf("second one %d", neighboors);
        }
        if (uv_get_cell(u, r - 1, c + 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r, c - 1) == true) {
            neighboors += 1;
        }

        if (uv_get_cell(u, r, c + 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c - 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c + 1) == true) {
            neighboors += 1;
        }
        //if in toroidal, do module to make sure there is no erros with %
    } else {
        int r_1 = ((r - 1) + u->rows) % u->rows;
        int c_1 = ((c - 1) + u->cols) % u->cols;
        if (uv_get_cell(u, r_1, c_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_1, c) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_1, c + 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r, c_1) == true) {
            neighboors += 1;
        }

        if (uv_get_cell(u, r, c + 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r + 1, c + 1) == true) {
            neighboors += 1;
        }
    }
    //return the number of neighboors
    return neighboors;
}
//print a universe
void uv_print(Universe *u, FILE *outfile) {
    //iterate through the rows
    for (int i = 0; i < u->rows; i++) {
        //iterate through the cols
        for (int t = 0; t < u->cols; t++) {
            //if the cell is alive, print an o
            if (u->grid[i][t] == true) {
                fprintf(outfile, "%s", "o");
            }
            //if it is dead, print a .
            if (u->grid[i][t] == false) {
                fprintf(outfile, "%s", ".");
            }
        }
        //print a new line
        fprintf(outfile, "%s", "\n");
    }
    return;
}
