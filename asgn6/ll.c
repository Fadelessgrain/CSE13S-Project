#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head; // Head sentinel node .
    Node *tail; // Tail sentinel node .
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *l = (LinkedList *) malloc(sizeof(LinkedList));
    l->length = 0;
    l->mtf = mtf;
    l->head = node_create(NULL, NULL);
    l->tail = node_create(NULL, NULL);
    l->head->next = l->tail;
    l->tail->prev = l->head;
    return l;
}

void ll_delete(LinkedList **ll) {
    if (*ll != NULL) {
        for (Node *n = (*ll)->head->next; n != (*ll)->tail; n = n->next) {
            Node *temp = (*ll)->head->next;
            node_delete(&((*ll)->head));
            (*ll)->head = temp;
        }
    }
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        if (strcmp(n->oldspeak, oldspeak) == 0) {
            if (ll->mtf == true) {
                n->prev->next = n->next;
                n->next->prev = n->prev;
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next->prev = n;
                ll->head->next = n;
            }

            return n;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    Node *n = node_create(oldspeak, newspeak);
    n->prev = ll->head;
    n->next = ll->tail->next;
    ll->head->next->prev = n;
    ll->head->next = n;
    ll->length += 1;
}

void ll_print(LinkedList *ll) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        node_print(n);
    }
}
