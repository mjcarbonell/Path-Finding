#include "stack.h"

#include "tsp.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Stack {
    uint32_t top; // INDEX OF THE NEXT EMPTY SLOT
    uint32_t capacity; // NUMBER OF ITEMS THAT CAN BE PUSHED
    int64_t *items; // ARRAY OF ITEMS, EACH WITH TYPE int64_t
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { // Freeing memory
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

uint32_t stack_size(Stack *s) {
    return (s->top);
}

bool stack_push(Stack *s,
    uint32_t x) { // We cannot push if stack is full. place itme in array and icnrement top
    if (s->top == (s->capacity)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s,
    uint32_t
        *x) { // We cant pop if stack is empty. Decrement top and place item in specified location
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s,
    uint32_t *
        x) { // If the stack is empty we make the x variable 0 becasue the salesman starts at the origin vertex AKA ZERO.
    if (stack_empty(s) == true) {
        *x = 0;
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    s->top += 1;
    return true;
}
void stack_copy(Stack *dst,
    Stack *
        src) { // Copying capacity and top first. Then we set all items in destination array to whatever is in source array
    dst->capacity = src->capacity;
    dst->top = src->top;
    for (uint64_t i = 0; i < (src->capacity); ++i) {
        dst->items[i] = src->items[i];
    }
}

void stack_print(Stack *s, FILE *outfile,
    char *cities
        []) { // we print origin first since we never add it to the path/stack. then we print all others.
    fprintf(outfile, "%s -> ", cities[0]);
    for (uint32_t i = 0; i < (s->top); i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}

/*int main(void){
	Stack *s = stack_create();
	stack_delete(&s);
	assert(s == NULL);
} */
