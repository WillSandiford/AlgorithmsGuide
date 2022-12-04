#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "Queue.h"
#include "Stack.h"

typedef struct edge *Edge;
typedef struct edges *Edges;
typedef struct graph *Graph;

/////////////////////////////////////

Graph GraphNew(int numV);

void GraphInsert(Graph g, Edge e);

void GraphRemove(Graph g, Edge e);

void GraphPrint(Graph g);

void GraphFree(Graph g);

void BFS(Graph g, int startVertex);

void DFS(Graph g, int startVertex);

Graph KruskalMST(Graph g);

Edges GraphSort(Graph g);

Edges ListNew(void);

void ListInsert(Edges l, Edge e);

void ListOrderedInsert(Edges l, Edge e);

void ListRemove(Edges l, Edge e);

void ListEnqueue(Edges l, Queue q, int *visited);

void ListPush(Edges l, Stack q, int *visited);

bool ListContains(Edges l, Edge e);

void ListPrint(Edges l);

void ListFree(Edges l);

Edge EdgeNew(int v, int w, double weight);

Edge EdgeCopy(Edge e);

bool EdgeCompare(Edge e1, Edge e2);

#endif