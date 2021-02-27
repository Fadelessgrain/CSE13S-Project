#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head; // Head sentinel node
    Node *tail; // Tail sentinel node
    bool mtf;
};

// allocates memory + creates a LinkedList and the struct of it
LinkedList *ll_create(bool mtf) {
    LinkedList *l = (LinkedList *) malloc(sizeof(LinkedList));
    if (l) {
        l->length = 0;
        l->mtf = mtf;
        // creates the head sentinel node
        l->head = node_create(NULL, NULL);
        // creates the tail sentinel node
        l->tail = node_create(NULL, NULL);
        // sets the head and tail to the correct place
        l->head->next = l->tail;
        l->tail->prev = l->head;
        l->head->prev = NULL;
        l->tail->next = NULL;
    }
    return l;
}

// frees memory for the LL as well as the memory for the sentinel nodes
void ll_delete(LinkedList **ll) {
    if (*ll) {
        // temp node that holds the head  node
        Node *temp = (*ll)->head->next;
        // loops as long as the temp node exists
        while (temp != NULL) {
            // delete's the prev node
            node_delete(&(temp->prev));
            // has the temp hold the next node
            temp = temp->next;
        }
        // free the last node (the tail)
        node_delete(&((*ll)->tail));
    }
    // frees the ll struct
    free(*ll);
    *ll = NULL;
}

//returns the length of the function
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// checks to see if a char is part of the LL
// Code below was inspire by the lecture slides
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // loops through the 'elements' in a node
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        // checks to see if oldspeak is in the LL
        if (strcmp(n->oldspeak, oldspeak) == 0) {
            // if the user wants to move to the front
            if (ll->mtf == true) {
                // the prev node will point to the next node
                n->prev->next = n->next;
                //the next node will point to the prev node
                n->next->prev = n->prev;
                // the next node will be the one that the head will
                // be pointing to
                n->next = ll->head->next;
                // the prev node is now the head node
                n->prev = ll->head;
                //the next head node points to the og node n
                ll->head->next->prev = n;
                // the next head node is now n
                ll->head->next = n;
            }
            return n;
        }
    }
    return NULL;
}

// code above was inspired by the lecture's slide

// inserts a new word into the LL
// Code below was isnpired by the lecture slides
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // a simple check to make sure that if the oldspeak is
    // already in the LL, exit
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }
    // creates a node
    Node *n = node_create(oldspeak, newspeak);
    // the next node will be node that head pointed to
    n->next = ll->head->next;
    // the prev node is now the head node
    n->prev = ll->head;
    // the next head node will be the node n
    ll->head->next->prev = n;
    // the node after the head node is the temp node (n) we created
    // thus, n is the at the front of the LL
    ll->head->next = n;
    // increment the length of the ll
    ll->length += 1;
    return;
}

// code above was inspired by the lecture slide

// prints a node
void ll_print(LinkedList *ll) {
    // a temp node taht will be used to print
    Node *n = ll->head->next;
    // loops through the LL
    for (uint32_t i = 0; i < ll_length(ll); i += 1) {
        // print one node
        node_print(n);
        // has the temp node point to the next node
        n = n->next;
    }
    return;
}
