#include "quick.h"

#include "stack.h"
#include "statistics.h"

// calculates the partition for quick sort
int64_t partition(uint32_t *a, int64_t lo, uint64_t hi) {
    int64_t x = ((hi - lo) / 2); // prevents over flow
    // stores the partition
    int64_t pivot = a[lo + (x)];
    // indexes of the elements
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    // loops as long as i < j
    do {
        i += 1;
        // increment compare counter
        compare();
        // increment the index of the element as long as a[i] is < pivot
        while (a[i] < pivot) {
            i += 1;
            // increment compare counter
            compare();
        }
        j -= 1;
        // increment compare counter
        compare();
        // decremenr the index of the element as long as a[j] > pivot
        while (a[j] > pivot) {
            // increment compare counter
            compare();
            j -= 1;
        }
        // if it finds an element greater, it swaps them
        if (i < j) {
            uint32_t temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            move();
        }

    } while (i < j);
    return j;
}

// function that calculates the quick_sort
void quick_sort(uint32_t *A, uint32_t n) {
    // sets the right and left index
    int64_t left = 0;
    int64_t right = (n - 1);
    // creates a stack
    Stack *s = stack_create();
    // pushes the index to the stack
    stack_push(s, left);
    stack_push(s, right);
    // as long as the stack is not empty
    while (!stack_empty(s)) {
        // pop the element last pushed
        stack_pop(s, &right);
        stack_pop(s, &left);
        // calculate the pivot partition
        int64_t p = partition(A, left, right);
        // sorts the elements of right
        if ((p + 1) < right) {
            stack_push(s, p + 1);
            stack_push(s, right);
        }
        // sorts the elements of the left
        if (left < p) {
            stack_push(s, left);
            stack_push(s, p);
        }
    }
    // free the stack
    stack_delete(&s);
}
