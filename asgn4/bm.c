#include "bm.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct BitMatrix {

    uint32_t rows;

    uint32_t cols;

    uint8_t **mat;

} BitMatrix;

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (m == NULL) {
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    if (m->mat == NULL) {
        return NULL;
    }
    uint32_t num_byte = (cols / 8 == 0) ? (cols / 8) : (cols / 8) + 1;
    for (uint32_t r = 0; r < rows; r += 1) {
        m->mat[r] = (uint8_t *) calloc(num_byte, sizeof(uint8_t));
        if (m->mat[r] == NULL) {
            return NULL;
        }
    }

    return m;
}

void bm_delete(BitMatrix **m) {
    for (uint32_t r = 0; r < (*m)->rows; r += 1) {
        free((*m)->mat[r]);
    }
    free((*m)->mat);
    free(*m);
    *m = NULL;
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    return (m)->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return (m)->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t col = ((c % 8) / 8);
    uint32_t mask = 1 << (col);
    m->mat[r][c] = (m->mat[r][c / 8]) | mask;
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t mask = ~(1 << (c % 8) / 8);
    m->mat[r][c / 8] = m->mat[r][c / 8] & mask;
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t col = ((c % 8) / 8);
    uint32_t mask = 1 << (col);
    m->mat[r][c / 8] = m->mat[r][c / 8] & mask;
    m->mat[r][c / 8] = m->mat[r][c / 8] >> col;
    return m->mat[r][c];
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < m->rows; i += 1) {
        for (uint32_t j = 0; j < m->cols; j += 1) {
            printf("%d\t", m->mat[i][j]);
        }
        printf("\n");
    }
}
