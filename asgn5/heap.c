#include "heap.h"

#include <stdbool.h>
#include <stdio.h>

uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && A[right - 1] > A[left - 1]) {
        return right;
    } else {
        return left;
    }
}

void fix_heap(uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(A, parent, last);
    while (parent <= (last / 2) && (!found)) {
        if (A[parent - 1] < A[great - 1]) {
            uint32_t temp = A[parent - 1];
            A[parent - 1] = A[great - 1];
            A[great - 1] = temp;
            parent = great;
            great = max_child(A, parent, last);

        } else {
            found = true;
        }
    }
}

void build_heap(uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t parent = (last / 2); parent > (first - 1); parent -= 1) {
        fix_heap(A, parent, last);
    }
}

void heap_sort(uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        uint32_t temp = A[first - 1];
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = temp;
        fix_heap(A, first, leaf - 1);
    }
}
