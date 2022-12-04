// Implementation of Sets according to COMP2521 - 2022 - T3 curriculum

#ifndef SET_H
#define SET_H

#include <stdbool.h>

#include "List.h" 

typedef List Set;

//////////////////////////////////

void SetFree(Set s);

Set SetNew(void);

void SetInsert(Set s, int member);

void SetDelete(Set s, int member);

bool SetMember(Set s, int member);

Set SetUnion(Set s1, Set s2);

Set SetIntersect(Set s1, Set s2);

void SetShow(Set s);

int SetCardinality(Set s);

#endif