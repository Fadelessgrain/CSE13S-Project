#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//struct Node {
//	char *oldspeak ;
//	char *newspeak ;
//	Node *next ;
//	Node *prev ;
//};

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = (oldspeak); //remember to fo a strdup
        n->newspeak = (newspeak); //remeber to do a strdup
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->newspeak);
        free((*n)->oldspeak);
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
