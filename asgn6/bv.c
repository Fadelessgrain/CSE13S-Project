#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    if (v) {
        v->length = length;
        uint32_t num_byte = length % 8 == 0 ? length / 8 : (length / 8) + 1;
        v->vector = calloc(num_byte, sizeof(uint8_t));
        return v;
    } else {
        return NULL;
    }
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] |= 1 << (i % 8);
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] = bv->vector[i / 8] & ~(1 << (i % 8));
    return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    return (bv->vector[i / 8] >> (i % 8)) & 1;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv_length(bv); i += 1) {
        uint32_t x = bv_get_bit(bv, i);
        printf("%d", x);
    }
    printf("\n");
}
