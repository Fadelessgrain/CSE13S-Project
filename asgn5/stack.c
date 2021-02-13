#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(void) {
    Stack *S = (Stack *) calloc(1, sizeof(Stack));
    S->top = 0;
    S->capacity = MIN_CAPACITY;
    S->items = (int64_t *) calloc(S->capacity, sizeof(int64_t));
    return S;
}
void stack_delete(Stack **s) {
    free((*s)->items);
    free((*s));
    *s = NULL;
    return;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity = (s->capacity) * 2;
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
    } else {
        s->items[s->top] = x;
        s->top += 1;
    }
    if (s->items == NULL) {
        return false;
    } else {
        return true;
    }
}

bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    } else {
        s->top -= 1;
        *x = s->items[s->top];
        return true;
    }
}
void stack_print(Stack *s) {
    if (stack_empty(s) == true) {
        exit(1);
    }

    for (uint32_t i = 0; i < sizeof(s->capacity); i += 1) {
        printf("%ld", s->items[i]);
    }
    printf("\n");
}
