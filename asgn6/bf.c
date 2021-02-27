#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

// defines the struct of a BF
struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt .
    uint64_t secondary[2]; // Secondary hash function salt .
    uint64_t tertiary[2]; // Tertiry hash function salt .
    BitVector *filter;
};

// allocates memory for a BF + creates the salts that will be used to hash
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Fear & Loathing in Las Vegas
        bf->primary[0] = 0x02d232593fbe42ff;
        bf->primary[1] = 0x3775cfbf0794f152;
        // A Moveable Feast
        bf->secondary[0] = 0xc1706bc17ececc04;
        bf->secondary[1] = 0xe9820aa4d2b8261a;
        // The Cremation of Sam McGee
        bf->tertiary[0] = 0xd37b01df0ae8f8d0;
        bf->tertiary[1] = 0x911d454886ca7cf7;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

// frees the memory allocated for the BV and the BF
void bf_delete(BloomFilter **bf) {
    if ((*bf)) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

// returns the length of the BF
uint32_t bf_length(BloomFilter *bf) {
    uint32_t L = bv_length((bf)->filter);
    return L;
}

// inserts a word into the BF
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // hashes all three of the salts
    uint64_t p = hash(bf->primary, oldspeak) % bf_length(bf);
    uint64_t s = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint64_t t = hash(bf->tertiary, oldspeak) % bf_length(bf);
    // sets all three of the salts in the BV
    bv_set_bit(bf->filter, p);
    bv_set_bit(bf->filter, s);
    bv_set_bit(bf->filter, t);
}

// checks if the word is in the BF
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // hash the three salts
    uint64_t p = hash(bf->primary, oldspeak) % bf_length(bf);
    uint64_t s = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint64_t t = hash(bf->tertiary, oldspeak) % bf_length(bf);
    // check to see if these salts were set in the BV
    uint64_t h1 = bv_get_bit(bf->filter, p);
    uint64_t h2 = bv_get_bit(bf->filter, s);
    uint64_t h3 = bv_get_bit(bf->filter, t);
    // if all three of the salts were set, return true
    if (h1 != 0 && h2 != 0 && h3 != 0) {
        return true;
        // else return false if even only one of them was not set
    } else {
        return false;
    }
}

// prints the BF (which really prints the BV)
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
