#include "hamming.h"

#include "bm.h"

#include <stdio.h>
#include <stdlib.h>

//typedef enum ham_rc {
//HAM_ERR= -1,
//HAM_OK= 0,
//HAM_ERR_OK = 1
//} ham_rc ;

static BitMatrix *G = NULL;
static BitMatrix *H = NULL;
static BitMatrix *m;

ham_rc ham_init(void) {
    G = bm_create(4, 8);
    H = bm_create(8, 4);
    bm_set_bit(G, 0, 0);
    bm_set_bit(G, 0, 5);
    bm_set_bit(G, 0, 6);
    bm_set_bit(G, 0, 7);
    bm_set_bit(G, 1, 1);
    bm_set_bit(G, 1, 4);
    bm_set_bit(G, 1, 6);
    bm_set_bit(G, 1, 7);
    bm_set_bit(G, 2, 2);
    bm_set_bit(G, 2, 4);
    bm_set_bit(G, 2, 5);
    bm_set_bit(G, 2, 7);
    bm_set_bit(G, 3, 3);
    bm_set_bit(G, 3, 4);
    bm_set_bit(G, 3, 5);
    bm_set_bit(G, 3, 6);
    bm_set_bit(H, 0, 1);
    bm_set_bit(H, 0, 2);
    bm_set_bit(H, 0, 3);
    bm_set_bit(H, 1, 0);
    bm_set_bit(H, 1, 2);
    bm_set_bit(H, 1, 3);
    bm_set_bit(H, 2, 0);
    bm_set_bit(H, 2, 1);
    bm_set_bit(H, 2, 3);
    bm_set_bit(H, 3, 0);
    bm_set_bit(H, 3, 1);
    bm_set_bit(H, 3, 2);
    bm_set_bit(H, 4, 0);
    bm_set_bit(H, 5, 1);
    bm_set_bit(H, 6, 2);
    bm_set_bit(H, 7, 3);
    if (G == NULL || H == NULL) {
        return HAM_ERR;
    } else {
        return HAM_OK;
    }
}
void ham_destroy(void) {
    bm_delete(&H);
    bm_delete(&G);
    return;
}

//void conver(int *a, int size, int num) {
//		for (int i = 0; i < size

//}

ham_rc ham_encode(uint8_t data, uint8_t *code) {
//	ham_init();
	m = bm_create(0, 4);
	for (uint8_t i = 0; i < 8; i += 1, data /=10) {
		bm_set_bit(m, i, 0);
	//	return m;
	}
	if (ham_init() == HAM_ERR) {
	return HAM_ERR;
	}else {
		for(uint8_t i = 0; i < bm_rows(G); i += 1) {
		for(uint8_t j = 0; j < bm_cols(G); j +=1) {
			for(uint8_t k = 0; k < 8; k += 1) {
			code[i][j] &= (**m)[i][j] ^ G[k][j]
			//	data+= code->mat[i][k] * (*G)->mat[k][j];
		//	uint8_t x =(*m)^ (*G);
			}
		}
//	printf("%d", data);
//	printf("%s", code);
	}


	//printf("%d", data);
//	ham_destory();
	return HAM_OK;
	}
}
//ham_rc ham_decode(uint8_t code, uint8_t *data) {

//}
