#include "quick.h"

#include "stack.h"
#include "statistics.h"

#include <stdio.h>
#include <stdlib.h>

int64_t partition(uint32_t *a, int64_t lo, uint64_t hi) {
    int64_t x = ((hi - lo) / 2);
    int64_t pivot = a[lo + (x)];

    int64_t i = lo - 1;
    int64_t j = hi + 1;
    do {
        i += 1;
        compare();
        while (a[i] < pivot) {
            compare();
            i += 1;
        }
        j -= 1;
        while (a[j] > pivot) {
            compare();
            ;

            j -= 1;
        }
        if (i < j) {

            uint32_t temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            move();
        }

    } while (i < j);
    return j;
}
void quick_sort(uint32_t *A, uint32_t n) {
    int64_t left = 0;
    int64_t right = (n - 1);
    ;
    Stack *s = stack_create();

    stack_push(s, left);
    stack_push(s, right);

    while (stack_empty(s) != true) {
        stack_pop(s, &right);
        stack_pop(s, &left);
        int64_t p = partition(A, left, right);
        if ((p + 1) < right) {
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
