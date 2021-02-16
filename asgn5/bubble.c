#include "bubble.h"

#include "statistics.h"

#include <stdbool.h>

// implrements the bubble alorithm
void bubble_sort(uint32_t *A, uint32_t n) {
    // sets swapped to false
    bool swapped = true;
    // while there are swaps being made, continue swapping
    while (swapped) {
        // sets the swap to false
        swapped = false;
        // loops through the elements of the array
        for (uint32_t i = 1; i < n; i += 1) {
            // increment comapre counter
            compare();
            // if it finds an element greater, swap them
            if (A[i] < A[i - 1]) {
                // increments my move counter
                move();
                uint32_t temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                // since a swapped happen, set it = true
                swapped = true;
            }
        }
        // decrement the size of the array because the last element is set
        // after each round
        n -= 1;
    }
}
