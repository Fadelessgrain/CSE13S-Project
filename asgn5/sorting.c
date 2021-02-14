#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqhr:n:p:"
int main(int argc, char **argv) {
    int opt = 0;
    uint32_t seed = 7092016;
    uint32_t size = 100;
    uint32_t print = 100;
    // uint32_t moves = 0;
    //   uint32_t compare = 0;
    Set s = set_empty();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            s = set_insert(s, 0); //buubles
            s = set_insert(s, 1); //shell
            s = set_insert(s, 2); //quick
            s = set_insert(s, 3); //heap
            break;
        case 'b': s = set_insert(s, 0); break;
        case 's': s = set_insert(s, 1); break;
        case 'q': s = set_insert(s, 2); break;
        case 'h': s = set_insert(s, 3); break;
        case 'r': seed = atoi(optarg); break;
        case 'p': print = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        default: 
		printf("error");
		}
    }
    srandom(seed);
    //	uint32_t *A = NULL;
    //	uint32_t *A = malloc(size * sizeof(uint32_t));
    uint32_t A[size];
    uint32_t B[size];
    uint32_t C[size];
    uint32_t D[size];
    // uint32_t *B = malloc(size * sizeof(uint32_t));
    //	uint32_t *C = malloc(size * sizeof(uint32_t));
    //uint32_t *D = malloc(size * sizeof(uint32_t));

    for (uint32_t i = 0; i < size; i += 1) {
        uint32_t masked_valued = random();
        masked_valued = masked_valued & 0x3FFFFFFF;
        A[i] = masked_valued;
        B[i] = masked_valued;
        C[i] = masked_valued;
        D[i] = masked_valued;
    }
    if (set_member(s, 0) == true) {
        bubble_sort(A, size);
        printf("Bubble Sort\n");
        printf("%u elements, moves, compares\n", size);
        // moves = 0;
        // compare = 0;
        for (uint32_t i = 0; i < print; i += 1) {
            printf("%13" PRIu32, A[i]);
        }
        printf("\n");
    }
    if (set_member(s, 1) == true) {
        shell_sort(B, size);
        for (uint32_t i = 0; i < print; i += 1) {
            printf("Shell Sort\n");
            printf("%13" PRIu32, B[i]);
        }
        printf("\n");
    }
    if (set_member(s, 2) == true) {
        quick_sort(C, size);
        for (uint32_t i = 0; i < print; i += 1) {
            printf("Bubble Sort\n");
            printf("%13" PRIu32, C[i]);
        }
        printf("\n");
    }
    if (set_member(s, 3) == true) {
        heap_sort(D, size);
        for (uint32_t i = 0; i < print; i += 1) {
            printf("Bubble Sort\n");
            printf("%13" PRIu32, D[i]);
        }
        printf("\n");
    }
    //	free(A);
    //	free(B);
    //	free(C);
    //	free(D);
}
