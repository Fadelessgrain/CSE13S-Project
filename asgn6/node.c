#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup_(char *s) {
    char *p;
    if (s == NULL) {
        return NULL;
    }
    size_t l = strlen(s) + 1;
    p = (char *) malloc(l);
    if (p) {
        strcpy(p, s);
    }
    return p;
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = strdup_(oldspeak);
        if (newspeak == NULL) {
            n->newspeak = strdup_(newspeak);
        } else {
            n->newspeak = NULL;
        }
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

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

void node_print(Node *n) {
    if (strlen(n->newspeak) == 0) {

        printf("%s\n", n->oldspeak);
    } else {

        printf("%s->%s\n", n->oldspeak, n->newspeak);
    }
}
