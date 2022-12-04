#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue *Queue;

Queue QueueNew(void);

void QueueEnqueue(Queue q, int item);

int QueueDequeue(Queue q);

void QueueFree(Queue q);

void QueuePrint(Queue q);

bool QueueIsEmpty(Queue q);

#endif