#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Stack Stack;

Stack *stack_create(uint32_t capacity);

void stack_delete(Stack **s);

uint32_t stack_size(Stack *s);

bool stack_empty(Stack *s);

bool stack_full(Stack *s);

bool stack_push(Stack *s, uint32_t x);

bool stack_pop(Stack *s, uint32_t *x);

bool stack_peek(Stack *s, uint32_t *x);

void stack_copy(Stack *dst, Stack *src);

void stack_print(Stack *s, FILE *outfile, char *cities[]);

#endif
