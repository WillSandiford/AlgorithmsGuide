// Queue implementation using linked lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Queue.h"

typedef struct node {
    int data;
    struct node *next;
} *Node;

struct queue {
    Node head;
    Node tail;
    int size;
};

typedef struct queue *Queue;

Node QueueNewNode(int item);

///////////////////////////////////////

Queue QueueNew(void) {
    Queue q = malloc(sizeof(*q));
    if (q == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
        return q;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void QueueEnqueue(Queue q, int item) {
    Node n = QueueNewNode(item);
    if (q->size == 0) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    q->size++;
}

int QueueDequeue(Queue q) {
    if (q->size == 0) {
        fprintf(stderr, "Cannot dequeue empty queue!\n");
        exit(EXIT_FAILURE);
    }
    int item = q->head->data;
    Node temp = q->head;
    q->head = q->head->next;
    free(temp);
    
    if (q->head == NULL) {
        q->tail = NULL;
    }
    q->size--;
    return item;
}

void QueueFree(Queue q) {
    Node current = q->head;
    Node temp;
    for (int i = 0; i < q->size; i++) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

void QueuePrint(Queue q) {
    Node current = q->head;
    for (int i = 0; i < q->size; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

bool QueueIsEmpty(Queue q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

Node QueueNewNode(int item) {
    Node n = malloc(sizeof(*n));
    n->data = item;
    n->next = NULL;
    return n;
}


