#include "bm.h"

#include <stdio.h>
#include <stdlib.h>

//structure for a bitMatrix
typedef struct BitMatrix {

    uint32_t rows;

    uint32_t cols;

    uint8_t **mat;

} BitMatrix;
//allocates memory for a bit matrix
//code below inspired by Shahiti's Lab section
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    //allocate memories for the structure
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (m == NULL) {
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;
    //allocates memories for the mat
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    if (m->mat == NULL) {
        return NULL;
    }
    //allocates memories for the cols
    uint32_t num_byte = (cols / 8 == 0) ? (cols / 8) : (cols / 8) + 1;
    for (uint32_t r = 0; r < rows; r += 1) {
        m->mat[r] = (uint8_t *) calloc(num_byte, sizeof(uint8_t));
        if (m->mat[r] == NULL) {
            return NULL;
        }
    }

    return m;
}
//code above inspired by Shahiti's Lab section
//frees the memory allocated
void bm_delete(BitMatrix **m) {
    //free the cols
    for (uint32_t r = 0; r < (*m)->rows; r += 1) {
        free((*m)->mat[r]);
    }
    //free the grid
    free((*m)->mat);
    //free the bitmat
    free(*m);
    *m = NULL;
    return;
}
//returns the number of rows
uint32_t bm_rows(BitMatrix *m) {
    return (m)->rows;
}
//returns the number of cols
uint32_t bm_cols(BitMatrix *m) {
    return (m)->cols;
}
//sets specific locations in the bit mat as 1
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    //makes sure we are in the corrent index (0,-7)
    //shifts by the cols
    uint32_t mask = 1 << ((c % 8) / 8);
    //ors the byte with the shift we did to set 1s
    m->mat[r][c] = (m->mat[r][c / 8]) | mask;
    return;
}
//clears specific locations in the bit mat to 0
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    //makes sure we are in the corrent index (0,-7) and shifts
    uint32_t mask = ~(1 << (c % 8) / 8);
    //ands our byte with the shift to see which ones need to 1s and 0s
    m->mat[r][c / 8] = m->mat[r][c / 8] & mask;
    return;
}
//gets the bit mat value from a specific location
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    //makes sure we are in the corrent index (0,-7)
    //shifts by the column
    uint32_t mask = 1 << ((c % 8) / 8);
    //we and m with the shift to check which ones are 1s or 0s
    m->mat[r][c / 8] = m->mat[r][c / 8] & mask;
    //shift it back again
    m->mat[r][c / 8] = m->mat[r][c / 8] >> ((c % 8) / 8);
    //return what's in the grid
    return m->mat[r][c];
}
//prints out the bit mat
void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < m->rows; i += 1) {
        for (uint32_t j = 0; j < m->cols; j += 1) {
            //     uint32_t x = bm_get_bit(m, i, j);
            printf("%d\t", m->mat[i][j]);
        }
        printf("\n");
    }
}
