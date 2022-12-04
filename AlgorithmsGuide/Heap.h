#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct heap *Heap;
typedef struct node *Item;

Heap HeapNew(int n);

void HeapInsert(Heap h, Item it);

void HeapFixUp(Item *items, int i);

void Swap(Item *items, int i, int j);

Item HeapDelete(Heap h);

void HeapFixDown(Item *items, int i, int n);

Item ItemNew(int data);

void HeapFree(Heap h);






#endif