#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"
#include "statistics.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//commands that can be parsed
#define OPTIONS "absqhr:n:p:"
int main(int argc, char **argv) {
    int opt = 0;
    //the default seed
    uint32_t seed = 7092016;
    //the default size
    uint32_t size = 100;
    //the defaulr print
    uint32_t print = 100;
    //creates a set
    Set s = set_empty();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            //whne a is passed, 'set' all the sortings
        case 'a':
            s = set_insert(s, 0); // sets buuble sort
            s = set_insert(s, 1); // sets shell sort
            s = set_insert(s, 2); // sets quick sort
            s = set_insert(s, 3); // sets heap  sort
            break;
            // when b is passed, set the bubble sort
        case 'b':
            s = set_insert(s, 0);
            break;
            // when s is pased, set the shell sort
        case 's': s = set_insert(s, 1); break;
        // when q is passed, set the q sort;
        case 'q':
            s = set_insert(s, 2);
            break;
            // when h is passed, set the heap sort;
        case 'h':
            s = set_insert(s, 3);
            break;
            //when r is passed, set the seed;
        case 'r':
            seed = atoi(optarg);
            break;
            // when p is passed, set the # of elements we have to print
        case 'p':
            print = atoi(optarg);
            break;
            //when n is passed, set the size of the array
        case 'n':
            size = atoi(optarg);
            break;
            // trow an error when nothing is parsed
        default: printf("Error, please enter a valid option");
        }
    }
    // sets the seed for random
    srandom(seed);
    // error handling so you don't print out more elements then the
    //size of Array
    if (print > size) {
        print = size;
    }
    //error handing so that you don't insert a valid array length
    if (size == 0) {
        printf("Indalid array length.");
        exit(1);
    }
    //if no sorting algorithm is parsed, throw an error
    if (!set_member(s, 0) && !set_member(s, 1) && !set_member(s, 2) && !set_member(s, 3)) {
        printf("Select at least one sort to perform\n");
    }
    // creates Array for bubbles
    uint32_t *A = malloc(size * sizeof(uint32_t));
    // creates Array for shell
    uint32_t *B = malloc(size * sizeof(uint32_t));
    // creates Array for quick
    uint32_t *C = malloc(size * sizeof(uint32_t));
    // creates Array for heap
    uint32_t *D = malloc(size * sizeof(uint32_t));
    // populates the array with random values (a value that was & to fit
    // into 30 bits
    for (uint32_t i = 0; i < size; i += 1) {
        uint32_t masked_valued = random();
        masked_valued = masked_valued & 0x3FFFFFFF;
        A[i] = masked_valued;
        B[i] = masked_valued;
        C[i] = masked_valued;
        D[i] = masked_valued;
    }
    //if 0 (value of bubble) was set, perform the algorithm
    if (set_member(s, 0) == true) {
        bubble_sort(A, size);
        // stores the moves, I did -3 from my total moves because my moves
        // function always added an extra move
        uint64_t moves = move() - 3;
        // stores the total comparisons, I did -1 from my total compares
        // because my function always ran an extra time
        uint32_t compares = compare() - 1;
        // resets my moves counter
        refresh(moves);
        // resets my compare counter
        refresh2(compares);
        printf("Bubble Sort\n");
        // print out the amout of elements, moves, and compares in the sort
        printf("%u elements, %lu moves, %u compares", size, moves, compares);
        // print out the # of elements that were parsed
        for (uint32_t i = 0; i < print; i += 1) {
            // makes sure we print in the correct format
            if (i % 5 == 0) {
                printf("\n");
            }
            // prints the array
            printf("%13" PRIu32, A[i]);
        }
        printf("\n");
    }
    // if 1 (value of shell) was set, perform the algorithm
    // same exact format as bubble, but for shell instead
    if (set_member(s, 1) == true) {
        shell_sort(B, size);
        printf("Shell Sort\n");
        // divided the moved by 3 becase we are only swapping
        // one thing and not 3
        uint64_t m = (move() - 3) / 3;
        uint32_t c = compare() - 1;
        refresh(m);
        refresh2(c);
        printf("%u elements, %lu moves, %u compares", size, m, c);
        for (uint32_t i = 0; i < print; i += 1) {
            if (i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, B[i]);
        }
        printf("\n");
    }
    //if 2 (value of quick) was set, perform the algorithm
    // same exact format as bubble and shell , but for quick instead
    if (set_member(s, 2) == true) {
        quick_sort(C, size);
        printf("Quick Sort\n");
        uint64_t m = move() - 3;
        uint32_t c = compare() - 1;
        refresh(m);
        refresh2(c);
        printf("%u elements, %lu moves, %u compares", size, m, c);
        for (uint32_t i = 0; i < print; i += 1) {
            if (i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, C[i]);
        }
        printf("\n");
    }
    //if 3 (value of heap) was set, perform the algorithm
    // same exact format as bubble, shell, and quick but for heap instead
    if (set_member(s, 3) == true) {
        heap_sort(D, size);
        printf("Heap Sort\n");
        uint64_t m = move() - 3;
        uint32_t c = compare();
        refresh(m);
        refresh(c);
        printf("%u elements, %lu moves, %u compares", size, m, c);
        for (uint32_t i = 0; i < print; i += 1) {
            if (i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, D[i]);
        }
        printf("\n");
    }
    // frees the memory of the arrays
    free(A);
    free(B);
    free(C);
    free(D);
}
