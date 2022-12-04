// Queue implementation using linked lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Stack.h"

typedef struct node {
    int data;
    struct node *next;
} *Node;

struct stack {
    Node head;
    int size;
};

typedef struct stack *Stack;

Node StackNewNode(int item);

///////////////////////////////////////

Stack StackNew(void) {
    Stack s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    s->head = NULL;
    s->size = 0;
    return s;
}

void StackPush(Stack s, int item) {
    Node n = StackNewNode(item);
    if (s->size == 0) {
        s->head = n;
    } else {
        n->next = s->head;
        s->head = n;
    }
    s->size++;
}

int StackPop(Stack s) {
    if (s->size == 0) {
        fprintf(stderr, "Cannot dequeue empty queue!\n");
        exit(EXIT_FAILURE);
    }
    int item = s->head->data;
    Node temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
    return item;
}

void StackFree(Stack s) {
    Node current = s->head;
    Node temp;
    for (int i = 0; i < s->size; i++) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

void StackPrint(Stack s) {
    Node current = s->head;
    for (int i = 0; i < s->size; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

bool StackIsEmpty(Stack s) {
    if (s->size == 0) {
        return true;
    }
    return false;
}

Node StackNewNode(int item) {
    Node n = malloc(sizeof(*n));
    n->data = item;
    n->next = NULL;
    return n;
}


