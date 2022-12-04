// Partial code taken and adjusted from COMP2521 - 2022 - T3 - lab04

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list *List;

// Creates a new empty list
List ListNew(void);

// Frees the given list
void ListFree(List l);

// Adds item to the end of list
void ListAppend(List l, int item);

// Prints all the items in a given list
void ListPrint(List l);

// Removes an item in the list at a specified index
void ListRemove(List l, int index);

// Removes the last item from the list and returns the data
int ListPop(List l);

// Finds whether an item is in the list
bool ListContains(List l, int item);

// Returns the number of items in the list
int  ListSize(List l);

// Returns the item at the item of the list
int ListItemAtIndex(List l, int index);

// Returns the ident the item belongs in the list
int ListIndexOfItem(List l, int item);

#endif
