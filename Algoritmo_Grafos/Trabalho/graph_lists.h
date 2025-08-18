#ifndef GRAPH_LISTS_H
#define GRAPH_LISTS_H

#include <stdbool.h>


typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;


typedef struct GraphLists {
    int numVertices;
    Node** adjLists; 
} GraphLists;


GraphLists* GL_createGraph(int V);


void GL_destroyGraph(GraphLists* graph);

void GL_addEdge(GraphLists* graph, int src, int dest, int weight);

void GL_sptDijkstra(GraphLists* graph, int src, int dist[], int pred[]);

void GL_printGraph(GraphLists* graph);

#endif 