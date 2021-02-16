#include "shell.h"

#include "gaps.h"
#include "statistics.h"

// imprements the shell algorithm
void shell_sort(uint32_t *A, uint32_t n) {
    // loops through the gaps
    for (uint32_t gap = 0; gap < *gaps; gap += 1) {
        // loops through the array
        for (uint32_t i = 0; i < n; i += 1) {
            uint32_t j = i;
            // stores the current element being examined
            uint32_t temp = A[i];
            // loop until we can find the right place for the temp
            while ((j >= gap) && (temp < A[j - gap])) {
                compare();
                // once it is found swap the elements
                A[j] = A[j - gap];
                move();
                j -= gap;
            }
            // places the sorted element back to the array
            A[j] = temp;
        }
    }
}
