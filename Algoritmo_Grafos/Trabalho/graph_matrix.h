#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdbool.h>


typedef struct GraphMatrix {
    int numVertices;
    int** matrix; 
} GraphMatrix;



GraphMatrix* GM_createGraph(int V);
void GM_destroyGraph(GraphMatrix* graph);
void GM_addEdge(GraphMatrix* graph, int src, int dest, int weight);
void GM_sptDijkstra(GraphMatrix* graph, int src, int dist[], int pred[]);
void GM_printGraph(GraphMatrix* graph);

#endif