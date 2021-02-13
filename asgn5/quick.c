#include "quick.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t particion(uint32_t *a, int64_t lo, uint64_t hi) {
    int64_t pivot = a[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;

    while (i < j) {
        i += 1;
        while (a[i] < pivot) {
            i += 1;
        }
        j -= 1;
        while (a[j] > pivot) {
            j -= 1;
            if (i < j) {
                uint32_t temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
    return j;
}

void quick_sort(uint32_t *A, uint32_t n) {
    int64_t left = 0;
    int64_t right = n - 1;
    Stack *s = stack_create();
    stack_push(s, left);
    stack_push(s, right);

    while (stack_empty(s) != true) {
        uint32_t hi = stack_pop(s, &left);
        uint32_t lo = stack_pop(s, &right);
        uint32_t p = particion(A, lo, hi);
        if (p + 1 < hi) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
    }
    stack_delete(&s);
}
