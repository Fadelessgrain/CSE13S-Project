#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// defines the struct of a stack
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// allocates memory for the stack
Stack *stack_create(void) {
    Stack *S = (Stack *) calloc(1, sizeof(Stack));
    S->top = 0;
    S->capacity = MIN_CAPACITY;
    S->items = (int64_t *) calloc(S->capacity, sizeof(int64_t));
    return S;
}

// frees the memory of a stack
void stack_delete(Stack **s) {
    free((*s)->items);
    free((*s));
    *s = NULL;
    return;
}

// checks to see if a stack is empty, retuns true if it is and f if it's not
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

// code below inspired by Euegene's section
// pushes a value into the stack
bool stack_push(Stack *s, int64_t x) {
    // if the stack has no memory, reallocate new memory
    if (s->top == s->capacity) {
        s->capacity = (s->capacity) * 2;
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
    }
    // pushes value to the top
    s->items[s->top] = x;
    s->top += 1;
    // checks to see if the allocation was succesful
    if (s->items == NULL) {
        return false;
    } else {
        return true;
    }
}
// code above inspired by Euegen's section

// pops element from the stack
bool stack_pop(Stack *s, int64_t *x) {
    // checks to see if the stack is empty
    if (s->top == 0) {
        return false;
    } else {
        // defeferences x and pops elements from stack
        s->top -= 1;
        *x = s->items[s->top];
        return true;
    }
}

// prints the elements in the stack
void stack_print(Stack *s) {
    if (stack_empty(s) == true) {
        exit(1);
    } else {

        for (uint32_t i = 0; i < sizeof(s->capacity); i += 1) {
            printf("%ld", s->items[i]);
        }
        printf("\n");
    }
}
