#include "word.h"

#include "code.h"

#include <stdlib.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) malloc(sizeof(Word));
    if (!w) {
        return NULL;
    }
    w->syms = syms;
    w->len = len;
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *nw = (Word *) malloc(sizeof(Word));
    nw->syms = calloc(w->len + 1, sizeof(uint8_t));
    for (uint8_t i = 0; i < w->len; i += 1) {
        nw->syms[i] = w->syms[i];
    }
    nw->syms[w->len] = sym;
    return nw;
}

void word_delete(Word *w) {
    free(w);
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) malloc(sizeof(MAX_CODE));
    if (wt) {
        wt[EMPTY_CODE] = word_create(NULL, 0);
    }
    return wt;
}

void wt_reset(WordTable *wt) {
    for (int i = START_CODE; i < MAX_CODE; i += 1) {
        if (i != EMPTY_CODE) {
            wt_delete(&wt[i]);
        }
    }
    return;
}

void wt_delete(WordTable *wt) {
    if (wt) {
        for (int i = 0; i < MAX_CODE; i += 1) {
            if (wt[i]) {
                wt_delete(&wt[i]);
            }
        }

        free(wt);
        return;
    }
}
