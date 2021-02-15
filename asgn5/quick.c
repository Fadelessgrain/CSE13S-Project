#include "quick.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int64_t particion(uint32_t *a, int64_t lo, uint64_t hi) {
    int64_t pivot = a[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;

    do {
        i += 1;
        while (a[i] < pivot) {
            i += 1;
        }
        j -= 1;
        while (a[j] > pivot) {
            j -= 1;
        }
        if (i < j) {
            uint32_t temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }

    } while (i < j);
    return j;
}

void quick_sort(uint32_t *A, uint32_t n) {
    int64_t left = 0;
    int64_t right = n - 1;
    Stack *s = stack_create();
    stack_push(s, left);
    stack_push(s, right);

    while (!stack_empty(s)) {
        uint32_t hi = 0;
        hi = stack_pop(s, &left);
        uint32_t lo = 0;
        lo = stack_pop(s, &right);
        uint32_t p = particion(A, left, right);
        if (p + 1 < right) {
            stack_push(s, p + 1);
            stack_push(s, right);
        }
        if (left < p) {
            stack_push(s, left);
            stack_push(s, p);
        }
    }
    stack_delete(&s);
}
