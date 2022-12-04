#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct node *Node;

Node NewNode(int key);

void TreeFree(Node n);

Node TreeInsertBST(Node n, int key);

Node TreeInsertAVL(Node n, int key);

Node TreeDelete(Node n, int key);

Node TreeJoin(Node root1, Node root2);

Node TreeRotateRight(Node n, int key);

Node TreeRotateLeft(Node n, int key);

int TreeFindHeight(Node root);

int TreeHeight(Node root);

void PreorderTraversal(Node n);

void InorderTraversal(Node n);

void PostorderTraversal(Node n);

#endif