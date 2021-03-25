#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// code below inspired by the class'  book implementation of strdup
// copies + allocates memory for a string
char *strdup_(char *s) {
    // makes sure we don't allocate memory for a  null string
    if (s == NULL) {
        return NULL;
    }
    char *p;
    size_t l = strlen(s) + 1;
    p = (char *) malloc(l);
    // makes sure malloc doesn't fail
    if (p == NULL) {
        return NULL;
    }
    strcpy(p, s);
    return p;
}

// code above inspired by the class' book implementation of strdup

// allocates memory for a node + its struct
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        // if oldspeak is null, copy it and allocate memory for it
        n->oldspeak = oldspeak = NULL ? NULL : strdup_(oldspeak);
        // if newspeak is null, copy it and allocate memory for it
        n->newspeak = newspeak = NULL ? NULL : strdup_(newspeak);
        n->next = NULL;
        n->prev = NULL;
        n->oldspeak = oldspeak;
        n->newspeak = newspeak;
    }
    return n;
}

// frees memory for the node struct as well as newspeak and oldspeak pointers
void node_delete(Node **n) {
    if (*n) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
        free(*n);
        *n = NULL;
    }
    return;
}

//prints a node in the format given to us in the asgn document
void node_print(Node *n) {
    // if oldspeak exists and new speaks also exists, print it in this format
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
        // if nespeak doesn't exists simply print out oldspeak
    } else if (n->oldspeak) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
