#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

typedef struct node *Node;
typedef struct list *List;
typedef struct hash *HashTable;

HashTable HashNew(int tableSize, int (*Hash)(int key, int tableSize));

List ListNew(void);

Node NodeNew(double item, int key);

void HashInsert(HashTable h, double item, int key);

void ListInsert(List l, double item, int key);

void HashDelete(HashTable h, double item, int key);

void ListDelete(List l, double item);

void HashPrint(HashTable h);

void ListPrint(List l);

void HashFree(HashTable h);

void ListFree(List l);

#endif