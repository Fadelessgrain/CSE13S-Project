#include "statistics.h"

#include <inttypes.h>
#include <stdio.h>

// cunter for moves
uint64_t m;
uint64_t move(void) {
    m += 3;
    return m;
}
// counter for compares
uint64_t c;
uint64_t compare(void) {
    c += 1;
    return c;
}

// helper function that refreshes the moves
uint64_t refresh(uint64_t m) {
    m = 0;
    c = 0;
    return m;
}
// helper function that refreshes the compares
uint64_t refresh2(uint64_t c) {
    c = 0;
    return c;
}
