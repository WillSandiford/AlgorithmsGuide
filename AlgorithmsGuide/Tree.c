#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Tree.h"

typedef struct node *Node;
struct node {
    int key;
    int height;
    Node right;
    Node left;
};

///////////////////////////////////

void TreeFree(Node n) {
    if (n == NULL) {
        return;
    }
    TreeFree(n->left);
    TreeFree(n->right);
    free(n);
}

Node TreeInsertBST(Node n, int key) {
    if (n == NULL) {
        return NewNode(key);
    }
    if (key < n->key) {
        n->left = TreeInsertBST(n->left, key);
    } else if (key > n->key) {
        n->right = TreeInsertBST(n->right, key);
    }
    return n;
}

Node TreeInsertAVL(Node n, int key) {
    if (n == NULL) {
        return NewNode(key);
    }
    if (key < n->key) {
        n->left = TreeInsertAVL(n->left, key);
    } else if (key > n->key) {
        n->right = TreeInsertAVL(n->right, key);
    } else {
        return n;
    }

    n->height = TreeFindHeight(n);
    int balance = TreeHeight(n->left) - TreeHeight(n->right);
    if (balance > 1) {
        if (key > n->left->key) {
            n->left = TreeRotateLeft(n->left, key);
        }
        return TreeRotateRight(n, key);
    } else if (balance < -1) {
        if (key < n->right->key) {
            n->right = TreeRotateRight(n->right, key);
        }
        return TreeRotateLeft(n, key);
    } else {
        return n;
    }
}

bool TreeContains(Node n, int key) {
    if (n == NULL) {
        return false;
    } else if (key < n->key) {
        return TreeContains(n->left, key);
    } else if (key > n->key) {
        return TreeContains(n->right, key);
    }
    return true;
}

Node TreeJoin(Node root1, Node root2) {
    if (root1 == NULL) {
        return root2;
    } else if (root2 == NULL) {
        return root1;
    }
    Node parent = NULL;
    Node current = root2;
    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }
    if (parent != NULL) {
        parent->left = current->right;
        current->right = root2;
    }
    current->left = root1;
    return current;
}

Node TreeDelete(Node n, int key) {
    if (n == NULL) {
        return n;
    }
    Node newNode = n;
    if (key < n->key) {
        n->left = TreeDelete(n->left, key);
    } else if (key > n->key) {
        n->right = TreeDelete(n->right, key);
    } else {
        if (n->left == NULL && n->right == NULL) {
            newNode = NULL;
        } else if (n->left == NULL) {
            newNode = n->right;
        } else if (n->right == NULL) {
            newNode = n->left;
        } else {
            newNode = TreeJoin(n->left, n->right);
        }
        free(n);
    }
    return newNode;
}

Node TreeRotateRight(Node n, int key) {
    if (n == NULL || n->left == NULL) {
        return n;
    }
    Node n2 = n->left;
    n->left = n2->right;
    n2->right = n;
    return n2;
}

Node TreeRotateLeft(Node n, int key) {
    if (n == NULL || n->right == NULL) {
        return n;
    }
    Node n2 = n->right;
    n->right = n2->left;
    n2->left = n;
    return n2;
}

int TreeFindHeight(Node root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = TreeFindHeight(root->left);
    int rightHeight = TreeFindHeight(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

int TreeHeight(Node root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

Node NewNode(int key) {
    Node n = malloc(sizeof(*n));
    n->key = key;
    n->height = 0;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void PreorderTraversal(Node n) {
    if (n == NULL) {
        return;
    }
    printf("%d ", n->key);
    InorderTraversal(n->left);
    InorderTraversal(n->right);
}

void InorderTraversal(Node n) {
    if (n == NULL) {
        return;
    }
    InorderTraversal(n->left);
    printf("%d ", n->key);
    InorderTraversal(n->right);
}

void PostorderTraversal(Node n) {
    if (n == NULL) {
        return;
    }
    PostorderTraversal(n->left);
    PostorderTraversal(n->right);
    printf("%d ", n->key);
}
