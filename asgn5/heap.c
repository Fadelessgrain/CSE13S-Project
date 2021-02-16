#include "heap.h"
#include "statistics.h"
#include <stdbool.h>
#include <stdio.h>

// thsi helper function finds the largest child and returns it
uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last) {
    // finds the left and right index
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    // compares the index
    if (A[right - 1] > A[left - 1]) {
        // increment counter for compare
        compare();
    }
    // checks to see which child / element is the largest
    if (right <= last && A[right - 1] > A[left - 1]) {
        compare();
        return right;
    } else {
        return left;
    }
}

// this helper function
void fix_heap(uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(A, parent, last);
    while (parent <= (last / 2) && (!found)) {
        compare();
        if (A[parent - 1] < A[great - 1]) {
            uint32_t temp = A[parent - 1];
            move();
            A[parent - 1] = A[great - 1];
            A[great - 1] = temp;
            parent = great;
            great = max_child(A, parent, last);

        } else {
            found = true;
        }
    }
}

// this helper function creates the heap ( tree) for the array
void build_heap(uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t parent = (last / 2); parent > (first - 1); parent -= 1) {
        fix_heap(A, parent, last);
    }
}

// this function sorts the array
void heap_sort(uint32_t *A, uint32_t n) {
    // find parent and last element to swap
    uint32_t first = 1;
    uint32_t last = n;
    // creates the heap
    build_heap(A, first, last);
    // loops to finds when the leaf > parent
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        // swaps elements
        uint32_t temp = A[first - 1];
        A[first - 1] = A[leaf - 1];
        // incrment counter fot moves
        move();
        A[leaf - 1] = temp;
        // create a new heap
        fix_heap(A, first, leaf - 1);
    }
}

