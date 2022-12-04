// Linked List implementation
// Partial code taken and adjusted from COMP2521 - 2022 - T3 - lab04
// to make a general List implementation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"

typedef struct node {
    int data;
    struct node *next;
} *Node;

typedef struct list {
    Node head;
    int numItems;
} *List;

Node NewNode(int item);

////////////////////////////////////////////////////////////////////////

List ListNew(void) {
    List l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->numItems = 0;
    return l;
}

void ListFree(List l) {
    Node current = l->head;
    for (int i = 0; i < l->numItems; i++) {
        Node temp = current;
        current = current->next;
        free(temp);
    }
    free(l);
}

void ListAppend(List l, int item) {
    if (l->numItems == 0) {
        l->head = NewNode(item);
        l->numItems++;
        return;
    }

    Node current = l->head;
    for (int i = 0; i < l->numItems - 1; i++) {
        current = current->next;
    }
    current->next = NewNode(item);
    l->numItems++;
}

void ListRemove(List l, int index) {
    if (index < 0 || index >= l->numItems || l->numItems == 0) {
        return;
    } else if (index == 0) {
        Node temp = l->head;
        l->head = l->head->next;
        l->numItems--;
        free(temp);
        return;
    }
    Node current = l->head;
    Node prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    l->numItems--;
    free(current);
}

int ListPop(List l) {
    if (l->numItems == 0) {
        printf("Cannot pop empty list\n");
        exit(1);
    }
    Node current = l->head;
    for (int i = 0; i < l->numItems - 1; i++) {
        current = current->next;
    }
    int item = current->data;
    ListRemove(l, l->numItems - 1);
    return item;
}

void ListPrint(List l) {
    if (l->numItems == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    Node current = l->head;
    for (int i = 0; i < l->numItems - 1; i++) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("%d]\n", current->data);
}

bool ListContains(List l, int item) {
    Node current = l->head;
    for (int i = 0; i < l->numItems; i++) {
        if (current->data == item) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int ListSize(List l) {
    return l->numItems;
}

int ListItemAtIndex(List l, int index) {
    if (index < 0 || index >= l->numItems) {
        printf("Index out of bounds\n");
        exit(1);
    }
    Node current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int ListIndexOfItem(List l, int item) {
    Node current = l->head;
    for (int i = 0; i < l->numItems; i++) {
        if (current->data == item) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

// Helpers //

Node NewNode(int item) {
    Node n = malloc(sizeof(*n));
    n->data = item;
    n->next = NULL;
    return n;
}
