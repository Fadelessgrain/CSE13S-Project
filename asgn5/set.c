#include "set.h"

#include <stdio.h>
#include <stdlib.h>

Set set_empty(void) {
    return 0;
}
bool set_member(Set s, uint8_t x) {
    uint32_t mask = 1 << (x);
    uint32_t result = s & mask;
    return result >> (x % 32);
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << (x % 32));
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << (x % 32));
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_complement(Set s) {
    return ~s;
}

Set set_difference(Set s, Set t) {
    return s & ~(t);
}
