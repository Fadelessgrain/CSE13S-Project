#include "statistics.h"

#include <inttypes.h>
#include <stdio.h>
uint32_t m;
uint32_t move(void) {
    m += 3;
    return m;
}

uint32_t c;
uint32_t compare(void) {
    c += 1;
    return c;
}

uint32_t refresh(uint32_t m, uint32_t c) {
    m = 0;
    c = 0;
    printf("moves: %u compares: %u\n", m, c);
    return m;
}

uint32_t com = 0;
uint32_t comparison(uint32_t *a, uint32_t temp, uint32_t x) {
    if (temp < a[x]) {
        com += 1;
        printf("com: %u\n", com);
    }
    return com;
}
