#include "universe.h"

#include <stdlib.h>
struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(int rows, int cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (int i = 0; i < rows; i++) {
        u->grid[i] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

void uv_delete(Universe *u) {
    for (int i = 0; i < u->rows; i++) {
        free(u->grid[i]);
    }
    free(u->grid);
    free(u);
    return;
}

int uv_rows(Universe *u) {
    return u->rows;
}

int uv_cols(Universe *u) {
    return u->cols;
}

bool out_of_bounds(Universe *u, int r, int c) {
    if (r >= u->rows & r < 0 & c >= u->cols & c < 0) {
        return false;
    } else {
        return true;
    }
}

void uv_live_cell(Universe *u, int r, int c) {
    //  if (r < u->rows & r >= 0 & c < u->cols & c >= 0) {
    int x = out_of_bounds(u, r, c);
    if (x == true) {
        u->grid[r][c] = true;
    }
    return;
}

void uv_dead_cell(Universe *u, int r, int c) {
    //    if (r < u->rows & r >= 0 & c < u->cols & c >= 0) {
    int x = out_of_bounds(u, r, c);
    if (x == true) {
        u->grid[r][c] = false;
    }
    return;
}

bool uv_get_cell(Universe *u, int r, int c) {
    // if (r >= u->rows & r < 0 & c >= u->cols & c < 0) {
    int x = out_of_bounds(u, r, c);
    if (x == false) {
        return false;
    } else {
        return u->grid[r][c];
    }
}

bool uv_populate(Universe *u, FILE *infile) {
    int row;
    int colum;
    while (fscanf(infile, "%d %d\n", &row, &colum) != EOF) {
        u->grid[row][colum] = true;
        int x = out_of_bounds(u, row, colum);
        if (x == false) {
            return false;
        } else {
            return true;
        }
    }
    return u;
}

int uv_census(Universe *u, int r, int c) {
    int neighboors = 0;
    if (u->toroidal == false) {
        if (uv_get_cell(u, r - 1, c - 1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r - 1, c) == true) {
            neighboors += 1;
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
    } else {
        int r_1 = (r - 1 + u->rows - 1) % u->rows;
        int c_1 = (c - 1 + u->cols - 1) % u->cols;
        int r_plus_1 = (r + 1 + u->rows - 1) % u->rows;
        int c_plus_1 = (c + 1 + u->cols - 1) % u->cols;
        if (uv_get_cell(u, r_1, c_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_1, c) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_1, c_plus_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r, c_1) == true) {
            neighboors += 1;
        }

        if (uv_get_cell(u, r, c_plus_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_plus_1, c_1) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_plus_1, c) == true) {
            neighboors += 1;
        }
        if (uv_get_cell(u, r_plus_1, c_plus_1) == true) {
            neighboors += 1;
        }
    }
    return neighboors;
}
void uv_print(Universe *u, FILE *outfile) {

    for (int i = 0; i > u->rows; i++) {
        for (int t = 0; t > u->cols; t++) {
            if (u->grid[u->rows][u->cols] == true) {
                fputc('o', outfile);
            } else {
                fputc('.', outfile);
            }
        }
    }
    return;
}
