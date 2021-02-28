#include "hash.h"

#include "ll.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

// defines the struct for a HT
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// allocates memory for ht + the LL
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

// frees the memory of the LL and the ht
void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i += 1) {
        ll_delete(&((*ht)->lists[i]));
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

// returns the size of the HT
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// checks if a word is in the ht
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // hashes the word
    uint32_t i = hash(ht->salt, oldspeak) % ht_size(ht);
    // checks if the hash isn't in the LL
    if (!ht->lists[i]) {
        return NULL;
    }
    // uses that hash to check if it's in the LL
    return ll_lookup(ht->lists[i], oldspeak);
}

//places a words in te HT
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // hashes the word
    uint32_t i = hash(ht->salt, oldspeak) % ht_size(ht);
    //makes sure the hash LL exists, if it doesn't create a LL
    if (!ht->lists[i]) {
        ht->lists[i] = ll_create(ht->mtf);
    }
    // uses the hash to isert it to a LL
    ll_insert(ht->lists[i], oldspeak, newspeak);
    return;
}

// prints the HT
// uses the format that was suggested in the document
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->lists[i] != NULL) {
            printf("lists[%u]: ", i);
            ll_print(ht->lists[i]);
        }
    }
}
