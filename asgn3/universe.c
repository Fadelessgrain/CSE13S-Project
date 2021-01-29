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

int main(void) {
    return 0;
}
