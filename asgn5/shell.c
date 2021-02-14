#include "shell.h"

#include "gaps.h"

#include <stdint.h>
#include <stdio.h>
//uint32_t compares;
//uint32_t moves;
void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t gap = 0; gap < *gaps; gap += 1) {
        for (uint32_t i = 0; i < n; i += 1) {

            uint32_t j = i;
            uint32_t temp = A[i];
            while (j >= gap && temp < A[j - gap]) {
                //     compares += 1;
                A[j] = A[j - gap];
                //    moves += 3;
                j -= gap;
            }
            A[j] = temp;
        }
    }
}
