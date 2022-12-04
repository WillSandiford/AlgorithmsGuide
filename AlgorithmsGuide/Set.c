// Set.c uses the List.c implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Set.h"

void SetFree(Set s) {
    ListFree(s);
}

Set SetNew(void) {
    return ListNew();
}

void SetInsert(Set s, int member) {
    if (!SetMember(s, member)) {
        ListAppend(s, member);
    }
}

void SetDelete(Set s, int member) {
    if (SetMember(s, member)) {
        int memberIndex = ListIndexOfItem(s, member);
        ListRemove(s, memberIndex);
    }
}

bool SetMember(Set s, int member) {
    return ListContains(s, member);
}

Set SetUnion(Set s1, Set s2) {
    Set s = SetNew();
    for (int i = 0; i < ListSize(s1); i++) {
        SetInsert(s, ListItemAtIndex(s1, i));
    }
    for (int j = 0; j < ListSize(s2); j++) {
        SetInsert(s, ListItemAtIndex(s2, j));
    }
    return s;
}

Set SetIntersect(Set s1, Set s2) {
    Set s = SetNew();
    for (int i = 0; i < ListSize(s1); i++) {
        int item1 = ListItemAtIndex(s1, i);
        for (int j = 0; j < ListSize(s2); j++) {
            int item2 = ListItemAtIndex(s2, j);
            if (item1 == item2) {
                SetInsert(s, item1);
            }
        }
    }
    return s;
}

void SetShow(Set s) {
    ListPrint(s);
}

int SetCardinality(Set s) {
    return ListSize(s);
}
