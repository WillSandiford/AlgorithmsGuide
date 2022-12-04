#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack *Stack;

Stack StackNew(void);

void StackPush(Stack q, int item);

int StackPop(Stack q);

void StackFree(Stack q);

void StackPrint(Stack q);

bool StackIsEmpty(Stack s);

#endif