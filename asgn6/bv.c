#include "bv.h"

#include <stdio.h>
#include <stdlib.h>



struct BitVector {
	uint32_t length ;
	uint8_t * vector ;
};

BitVector *bv_create(uint32_t length) {
	BitVector *v = (BitVector*)calloc(1, sizeof(BitVector));
	v->length = length;
	v->vector = (uint8_t *)calloc(length, sizeof(uint8_t));
	return v;
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
		uint32_t mask = 1 << ((i % 8) / 8);
      	bv->vector[i / 8] |= mask; 
       return;
}


void bv_clr_bit(BitVector *bv, uint32_t i) {
	uint32_t mask = ~(1 << (i % 8) / 8);
	bv->vector[i / 8] &= mask;
	return;

}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
		uint32_t mask = 1 << ((i % 8) / 8);
       bv->vector[i / 8] = bv->vector[i / 8] & mask;
       bv->vector[i / 8] = bv->vector[i / 8] >> ((i % 8) / 8);
       return (bv->vector[i / 8]);

}

void bv_print(BitVector *bv) {
	for (uint32_t i = 0; i < bv->length; i += 1) {
		printf("%d\t", bv->vector[i]);
       }
           printf("\n");
 }
