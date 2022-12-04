// A main file to test all the algorithms

#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

int main(void) {
    Node t = NewNode(4);

    t = TreeInsertAVL(t, 1);
    t = TreeInsertAVL(t, 2);
    t = TreeInsertAVL(t, 0);

    InorderTraversal(t);
    TreeFree(t);

    return 0;
}
