// Adjacency List graph implementation


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"
#include "Queue.h"
#include "Stack.h"

typedef struct edge {
    int v;
    int w;
    double weight;
    struct edge *next;
} *Edge;

typedef struct edges {
    int nE;
    Edge head;
} *Edges;

typedef struct graph {
    int nV;
    Edges *edges;
} *Graph;


//////////////////////////////////////////

Graph GraphNew(int numV) {
    Graph g = malloc(sizeof(*g));
    g->nV = numV;
    g->edges = malloc(numV * sizeof(Edges));
    for (int i = 0; i < numV; i++) {
        g->edges[i] = ListNew();
    }
    return g;
}

void GraphInsert(Graph g, Edge e) {
    ListOrderedInsert(g->edges[e->v], e);
}

void GraphRemove(Graph g, Edge e) {
    if (ListContains(g->edges[e->v], e)) {
        ListRemove(g->edges[e->v], e);
    }
}

void GraphPrint(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        printf("%d: ", i);
        ListPrint(g->edges[i]);
    }
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        ListFree(g->edges[i]);
    }
    free(g);
}

void BFS(Graph g, int startVertex) {
    int *visited = calloc(g->nV, sizeof(int));
    Queue q = QueueNew();
    QueueEnqueue(q, startVertex);
    for (int i = 0; i < g->nV; i++) {
        int v = QueueDequeue(q);
        visited[v] = 1;
        printf("%d ", v);
        ListEnqueue(g->edges[v], q, visited);
    }
    free(visited);
    printf("\n");
}

void DFS(Graph g, int startVertex) {
    int *visited = calloc(g->nV, sizeof(int));
    Stack s = StackNew();
    StackPush(s, startVertex);
    for (int i = 0; i < g->nV; i++) {
        int v = StackPop(s);
        visited[v] = 1;
        printf("%d ", v);
        ListPush(g->edges[v], s, visited);
    }
    free(visited);
    printf("\n");
}

Graph KruskalMST(Graph g) {
    int *visited = calloc(g->nV, sizeof(int));
    Graph mst = GraphNew(g->nV);
    Edges sortedEdges = GraphSort(g);
    Edge e = sortedEdges->head;
    int numInserted = 0;
    for (int i = 0; i < sortedEdges->nE; i++) {
        if (numInserted == mst->nV - 1) {
            ListFree(sortedEdges);
            return mst;
        }
        if (visited[e->v] == 0) {
            GraphInsert(mst, EdgeCopy(e));
            numInserted++;
        }
        e = e->next;
    }
    ListFree(sortedEdges);
    printf("No MST exists");
    exit(1);
}

Edges GraphSort(Graph g) {
    Edges sortedList = ListNew();
    for (int i = 0; i < g->nV; i++) {
        Edges l = g->edges[i];
        Edge current = l->head;
        for (int j = 0; j < l->nE; j++) {
            ListOrderedInsert(sortedList, EdgeCopy(current));
            current = current->next;
        }
    }
    return sortedList;
}

Edges ListNew(void) {
    Edges l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->nE = 0;
    return l;
}

void ListInsert(Edges l, Edge e) {
    if (l->head == NULL) {
        l->head = e;
        l->nE++;
        return;
    } else if (ListContains(l, e)) {
        return;
    }
    Edge current = l->head;
    for (int i = 0; i < l->nE - 1; i++) {
        current = current->next;
    }
    current->next = e;
    l->nE++;
}

void ListOrderedInsert(Edges l, Edge e) {
    if (l->head == NULL) {
        l->head = e;
        l->nE++;
        return;
    } else if (e->weight < l->head->weight) {
        e->next = l->head;
        l->head = e;
        l->nE++;
        return;
    }
    
    Edge current = l->head->next;
    Edge prev = l->head;
    while (current != NULL && e->weight > current->weight) {
        prev = current;
        current = current->next;        
    }
    prev->next = e;
    e->next = current;
    l->nE++;
}

void ListRemove(Edges l, Edge e) {
    if (EdgeCompare(l->head, e)) {
        Edge temp = l->head;
        l->head = l->head->next;
        l->nE--;
        free(temp);
        return;
    }
    Edge current = l->head;
    Edge prev = current;
    for (int i = 0; i < l->nE; i++) {
        if (EdgeCompare(current, e)) {
            prev->next = current->next;
            free(current);
            l->nE--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void ListEnqueue(Edges l, Queue q, int *visited) {
    Edge current = l->head;
    for (int i = 0; i < l->nE; i++) {
        if (visited[current->w] == 0) {
            QueueEnqueue(q, current->w);
            visited[current->w] = 1;
        }
        current = current->next;
    }
}

void ListPush(Edges l, Stack s, int *visited) {
    Edge current = l->head;
    for (int i = 0; i < l->nE; i++) {
        if (visited[current->w] == 0) {
            StackPush(s, current->w);
            visited[current->w] = 1;
        }
        current = current->next;
    }
}

bool ListContains(Edges l, Edge e) {
    if (l->head == NULL) {
        return false;
    }
    Edge current = l->head;
    for (int i = 0; i < l->nE; i++) {
        if (EdgeCompare(current, e)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void ListPrint(Edges l) {
    Edge current = l->head;
    for (int i = 0; i < l->nE; i++) {
        printf("%d (%.1f) ", current->w, current->weight);
        current = current->next;
    }
    printf("\n");
}

void ListFree(Edges l) {
    Edge current = l->head;
    for (int i = 0; i < l->nE; i++) {
        Edge temp = current;
        current = current->next;
        free(temp);
    }
    free(l);
}

Edge EdgeNew(int v, int w, double weight) {
    Edge e = malloc(sizeof(*e));
    e->v = v;
    e->w = w;
    e->weight = weight;
    e->next = NULL;
    return e;
}

Edge EdgeCopy(Edge e) {
    Edge copy = EdgeNew(e->v, e->w, e->weight);
    copy->next = NULL;
    return copy;
}

bool EdgeCompare(Edge e1, Edge e2) {
    return e1->v == e2->v && e1->w == e2->w;
}





