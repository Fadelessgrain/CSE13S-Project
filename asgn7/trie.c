#include "trie.h"

#include "code.h"

#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
    TrieNode *n = (TrieNode *) malloc(sizeof(TrieNode));
    if (!n) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET; i += 1) {
        n->children[i] = NULL;
    }
    n->code = code;
    return n;
}

void trie_node_delete(TrieNode *n) {
    if (n) {
        free(n);
        n = NULL;
        return;
    }
}

TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i += 1) {
        if (root->children[i]) {
            trie_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }
    return;
}

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

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n->children[sym] == NULL) {
        return NULL;
    }
    return n->children[sym];
}
