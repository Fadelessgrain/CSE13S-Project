#include "hamming.h"

#include "bm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//'creates' the G and H_T matrices
static BitMatrix *G = NULL;
static BitMatrix *H = NULL;
//sets the values inside the G and H_T matrices
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
    //if creating either one fails, return ham_err
    if (G == NULL || H == NULL) {
        return HAM_ERR;
    } else {
        //else return hma ok
        return HAM_OK;
    }
}
//frees the memory of G  and H_T
void ham_destroy(void) {
    bm_delete(&H);
    bm_delete(&G);
    return;
}
//enocdes a nibble at a time and stores it in a pointer
//code below inspired by Sahiri's lab section
ham_rc ham_encode(uint8_t data, uint8_t *code) {
    //if init Gor H_T fails, return error
    *code = data << 4;

    if (ham_init() == HAM_ERR) {
        return HAM_ERR;
    } else {
        //loops through the rows of G
        for (uint8_t i = 0; i < bm_rows(G); i += 1) {
            //loops the cols of data
            for (uint8_t j = 0; j < 1; j += 1) {
                // loops through the cols of G
                for (uint8_t k = 0; k < bm_cols(G); k += 1) {
                    //will store the result
                    uint8_t y = 0;
                    //get the bit at the specific location
                    uint8_t x = bm_get_bit(G, i, j);
                    // y = (data | *code) >> 1;
                    //times the bit by data
                    uint8_t z = (x & data);
                    //add the bits toegther
                    y = (*code) ^ z;
                    //send that result to the pointer
                    *code = y;
                }
            }
        }
    }
    //else return ok
    return HAM_OK;
}
//code abve inspired by sahiri's lab section

//decodes a message
ham_rc ham_decode(uint8_t code, uint8_t *data) {
    for (uint8_t i = 0; i < bm_rows(G); i += 1) {
        //loops the cols of data
        for (uint8_t j = 0; j < 1; j += 1) {
            // loops through the cols of G
            for (uint8_t k = 0; k < bm_cols(H); k += 1) {
                //will store the result
                uint8_t y = 0;
                //get the bit at the specific location
                uint8_t x = bm_get_bit(H, i, j);
                // y = (data | *code) >> 1;
                //times the bit by the code
                uint8_t z = (x & code);
                //add the bits toegther
                y = (*data) ^ z;
                //send that result to the pointer
                *data = y;
            }
        }
    }
    //if there was no error, return ham ok
    if (data == 0000) {
        return HAM_OK;
    } else {
        //else return an error
        return HAM_ERR;
    }
}
