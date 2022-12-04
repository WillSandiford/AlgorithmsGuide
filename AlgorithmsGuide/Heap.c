#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "Heap.h"

typedef struct heap *Heap;
typedef struct node *Item;

struct node {
    int data;
};

struct heap {
    Item *items;
    int numItems;
    int maxItems;
};

///////////////////////////////////////

Heap HeapNew(int n) {
    Heap h = malloc(sizeof(*h));
    if (h == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    h->numItems = 0;
    h->maxItems = n;
    h->items = malloc((n + 1) * sizeof(Item));
    return h;
}

void HeapInsert(Heap h, Item it) {
    assert(h->numItems < h->maxItems);
    h->numItems++;
    h->items[h->numItems] = it;
    HeapFixUp(h->items, h->numItems);
}

void HeapFixUp(Item *items, int i) {
    while (i > 1 && items[i / 2]->data < items[i]->data) {
        Swap(items, i, i / 2);
        i /= 2;
    }
}

void Swap(Item *items, int i, int j) {
    Item temp = items[i];
    items[i] = items[j];
    items[j] = temp;
}

Item HeapDelete(Heap h) {
    Item top = h->items[1];
    h->items[1] = h->items[h->numItems];
    h->numItems--;
    HeapFixDown(h->items, 1, h->numItems);
    printf("%d\n", top->data);
    return top;
}

void HeapFixDown(Item *items, int i, int n) {
    while (2 * i <= n) {
        int j = 2 * i;
        if (j < n && items[j] < items[j + 1]) {
            j++;
        }
        if (items[i] >= items[j]) {
            break;
        }
        Swap(items, i, j);
        i = j;
    }
}

void HeapFree(Heap h) {
    for (int i = 0; i < h->numItems; i++) {
        free(h->items[i]);
    }
    free(h);
}

Item ItemNew(int data) {
    Item it = malloc(sizeof(*it));
    it->data = data;
    return it;
}
