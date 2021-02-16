#include "set.h"

#include <stdio.h>
#include <stdlib.h>

// creates an empty set 
Set set_empty(void) {
    return 0;
}

// checks to see if an element  has been set by shifting it in tha range of 
// % 32 and then & the result in the set to find whoch ones are set,
// the shits it again to get the element 
bool set_member(Set s, uint8_t x) {
    uint32_t mask = 1 << (x);
    uint32_t result = s & mask;
    return result >> (x % 32);
}

// inserts / sets an element 
// shifts x by % 32 to stay in range, ors the shift with the set to insert
// a new element
Set set_insert(Set s, uint8_t x) {
    return s | (1 << (x % 32));
}
// removes an element from a set by shifting it by x % 32 (to keep in range)
// ands the result with the s to see which ones are set
Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << (x % 32));
}

// returns the elements a set has in common
Set set_intersect(Set s, Set t) {
    return s & t;
}
// returns the union of two sets 
Set set_union(Set s, Set t) {
    return s | t;
}

// returns the oppositive of a set
Set set_complement(Set s) {
    return ~s;
}


// returns what two sets have in difference
Set set_difference(Set s, Set t) {
    return s & ~(t);
}
