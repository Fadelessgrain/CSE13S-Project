#include "word.h"

#include "code.h"

#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    if (w) {
        w->len = len;
        w->syms = (uint8_t *) calloc(1, len * sizeof(uint8_t));
        if (w->syms) {
            //  	for (uint8_t i = 0; i < w->len; i += 1) {
            //	w->syms[i] = *syms;
            memcpy(w->syms, syms, len);
            //  	}
        }
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    if (!w) {
        return NULL;
    }
    Word *nw = (Word *) malloc(sizeof(Word));
    if (nw) {
        nw->len = w->len + 1;
        nw->syms = (uint8_t *) malloc((nw->len) * sizeof(uint8_t));
        if (nw->syms) {
            for (uint8_t i = 0; i < w->len; i += 1) {
                nw->syms[i] = w->syms[i];
            }
            nw->syms[w->len] = sym;
        }
    }
    word_delete(nw);
    return nw;
}

void word_delete(Word *w) {
    if (w) {
        free(w->syms);
        w->syms = NULL;
        free(w);
        w = NULL;
    }
    return;
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    if (wt) {
        wt[EMPTY_CODE] = (Word *) calloc(1, sizeof(Word));
        //	word_create(NULL, 0);
    }
    return wt;
}

void wt_reset(WordTable *wt) {
    if (wt) {
        for (int i = EMPTY_CODE; i < MAX_CODE; i += 1) {
            if (wt[i]) {
                word_delete(wt[i]);
                wt[i] = NULL;
            }
        }
    }
    return;
}

void wt_delete(WordTable *wt) {
    if (!wt) {
        return;
    }
    for (int i = EMPTY_CODE; i < MAX_CODE; i += 1) {
        if (wt[i]) {
            word_delete(wt[i]);
            wt[i] = NULL;
        }
    }
    free(wt);
    wt = NULL;
    return;
}
