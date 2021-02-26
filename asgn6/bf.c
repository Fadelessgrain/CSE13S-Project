#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
struct BloomFilter {

    uint64_t primary[2];
    // Primary hash function salt .

    uint64_t secondary[2]; // Secondary hash function salt .

    uint64_t tertiary[2]; // Tertiary hash function salt .

    BitVector *filter;
};

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

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_length(BloomFilter *bf) {
    uint32_t L = bv_length((bf)->filter);
    return L;
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint64_t p = hash(bf->primary, oldspeak) % bf_length(bf);
    uint64_t s = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint64_t t = hash(bf->tertiary, oldspeak) % bf_length(bf);
    bv_set_bit(bf->filter, p);
    bv_set_bit(bf->filter, s);
    bv_set_bit(bf->filter, t);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint64_t p = hash(bf->primary, oldspeak) % bf_length(bf);
    uint64_t s = hash(bf->secondary, oldspeak) % bf_length(bf);
    uint64_t t = hash(bf->tertiary, oldspeak) % bf_length(bf);
    uint64_t h1 = bv_get_bit(bf->filter, p);
    uint64_t h2 = bv_get_bit(bf->filter, s);
    uint64_t h3 = bv_get_bit(bf->filter, t);
    if (h1 == 1 && h2 == 1 && h3 == 1) {
        return 1;

    } else {
        return 0;
    }
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
