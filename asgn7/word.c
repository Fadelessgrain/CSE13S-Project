#include "word.h"

#include "code.h"

#include <stdlib.h>
#include <string.h>

// creates a new word + allocates memory for it + its sym
Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) malloc(sizeof(Word));
    if (w) {
        w->len = len;
        w->syms = (uint8_t *) malloc(len * sizeof(uint8_t));
        if (w->syms) {
            for (uint32_t i = 0; i < len; i += 1) {
                w->syms[i] = syms[i];
            }
        }
    }
    return w;
}

// appends a sym to a word
Word *word_append_sym(Word *w, uint8_t sym) {
    if (!w) {
        return NULL;
    }
    // create a new temp word
    Word *nw = (Word *) calloc(1, sizeof(Word));
    if (nw) {
        nw->len = w->len + 1;
        // allocate memory for the sym
        nw->syms = (uint8_t *) malloc((nw->len + 1) * sizeof(uint8_t));
        if (nw->syms) {
            // copy the sym
            for (uint8_t i = 0; i < w->len; i += 1) {
                nw->syms[i] = w->syms[i];
            }
            // set the temp sym to the sym parameter
            nw->syms[w->len] = sym;
        }
    }
    // return the new word
    return nw;
}

// frees the memory of w word + the syms
void word_delete(Word *w) {
    if (w) {
        free(w->syms);
        w->syms = NULL;
        free(w);
        w = NULL;
    }
    return;
}

// creates a word table
// code below inspired by Gabe's session and Eugene's session
WordTable *wt_create(void) {
    // allocates memory for a word table
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    if (wt) {
        // allocates memory for an empty code
        wt[EMPTY_CODE] = (Word *) calloc(1, sizeof(Word));
    }
    // return thr word table
    return wt;
}
// code below inspired by Gabe's session and Eugene's session

//resets the content of the word table by delting them
void wt_reset(WordTable *wt) {
    if (wt) {
        for (int i = START_CODE; i < MAX_CODE; i += 1) {
            if (wt[i]) {
                word_delete(wt[i]);
                wt[i] = NULL;
            }
        }
    }
    return;
}

// deletes the memory and frees a word table
void wt_delete(WordTable *wt) {
    if (!wt) {
        return;
    }
    for (int i = 0; i < MAX_CODE; i += 1) {
        if (wt[i]) {
            word_delete(wt[i]);
            wt[i] = NULL;
        }
    }
    free(wt);
    wt = NULL;
    return;
}
