#include "trie.h"

#include "code.h"

#include <stdio.h>
#include <stdlib.h>

// creates a new trie + allocates memory for it
TrieNode *trie_node_create(uint16_t code) {
    TrieNode *n = (TrieNode *) malloc(sizeof(TrieNode));
    if (!n) {
        return NULL;
    }
    // sets the children to null
    for (int i = 0; i < ALPHABET; i += 1) {
        n->children[i] = NULL;
    }
    n->code = code;
    return n;
}

// frees the memory of a trie
void trie_node_delete(TrieNode *n) {
    if (n) {
        free(n);
        n = NULL;
        return;
    }
}

// creates an emty trie
TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

// restes the root/chidlren of a trie w/out reseting the parent
void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i += 1) {
        if (root->children[i]) {
            trie_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }
    return;
}

// deletes a trie + its chidlren
void trie_delete(TrieNode *n) {
    if (n) {
        for (int i = 0; i < ALPHABET; i += 1) {
            trie_delete(n->children[i]);
            n->children[i] = NULL;
        }
        trie_node_delete(n);
    }
    return;
}

// check if a sym is in the trie struct
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n->children[sym] == NULL) {
        return NULL;
    }
    return n->children[sym];
}
