#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Hash.h"

typedef struct node *Node;
typedef struct list *List;
typedef struct hash *HashTable;

struct node {
    int key;
    double data;
    Node next;
};

struct list {
    int size;
    Node head;
};

struct hash {
    int tableSize;
    int (*Hash)(int key, int tableSize);
    List *lists;
};

/////////////////////////////////////

HashTable HashNew(int tableSize, int (*Hash)(int key, int tableSize)) {
    HashTable h = malloc(sizeof(*h));
    h->lists = malloc(tableSize * sizeof(List));
    for (int i = 0; i < tableSize; i++) {
        h->lists[i] = ListNew();
    }
    h->tableSize = tableSize;
    h->Hash = Hash;
    return h;
}

List ListNew(void) {
    List l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->size = 0;
    return l;
}

Node NodeNew(double item, int key) {
    Node n = malloc(sizeof(*n));
    n->key = key;
    n->data = item;
    n->next = NULL;
    return n;
}

void HashInsert(HashTable h, double item, int key) {
    int index = h->Hash(key, h->tableSize);
    ListInsert(h->lists[index], item, key);
}

// Ordered Insert
void ListInsert(List l, double item, int key) {
    Node n = NodeNew(item, key);
    if (l->head == NULL) {
        l->head =n;
        l->size++;
        return;
    } else if (item < l->head->data) {
        n->next = l->head;
        l->head = n;
        l->size++;
        return;
    }
    Node current = l->head->next;
    Node prev = l->head;
    while (current != NULL && item > current->data) {
        prev = current;
        current = current->next;        
    }
    prev->next = n;
    n->next = current;
    l->size++;
}

void HashDelete(HashTable h, double item, int key) {
    ListDelete(h->lists[key], item);
}

void ListDelete(List l, double item) {
    if (l->head == NULL) {
        return;
    } else if (l->size == 1 && l->head->data == item) {
        free(l->head);
        return;
    }
    Node current = l->head;
    Node prev = NULL;
    for (int i = 0; i < l->size; i++) {
        if (current->data == item) {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashPrint(HashTable h) {
    for (int i = 0; i < h->tableSize; i++) {
        printf("%d: ", i);
        ListPrint(h->lists[i]);
    }
}

void ListPrint(List l) {
    Node current = l->head;
    for (int i = 0; i < l->size; i++) {
        printf("%.2f ", current->data);
        current = current->next;
    }
    printf("\n");
}

void HashFree(HashTable h) {
    for (int i = 0; i < h->tableSize; i++) {
        ListFree(h->lists[i]);
    }
    free(h);
}

void ListFree(List l) {
    Node current = l->head;
    for (int i = 0; i < l->size; i++) {
        Node temp = current;
        current = current->next;
        free(temp);
    }
}
