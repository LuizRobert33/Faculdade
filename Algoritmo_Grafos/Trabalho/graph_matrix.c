#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph_matrix.h"

GraphMatrix* GM_createGraph(int V) {
    GraphMatrix* graph = malloc(sizeof(GraphMatrix));
    graph->numVertices = V;
    graph->matrix = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = 0; 
        }
    }
    return graph;
}

void GM_destroyGraph(GraphMatrix* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

void GM_addEdge(GraphMatrix* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
}

void GM_printGraph(GraphMatrix* graph) {
    printf("Representação do Grafo (Matriz de Adjacências):\n   ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d ", i);
    }
    printf("\n---");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("---");
    }
    printf("\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d|", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%2d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}


static int findMinDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void GM_sptDijkstra(GraphMatrix* graph, int src, int dist[], int pred[]) {
    int V = graph->numVertices;
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = findMinDistance(dist, sptSet, V);
        if (u == -1) break;

        sptSet[u] = true;

        
        for (int v = 0; v < V; v++) {
            int weight = graph->matrix[u][v];
            if (weight > 0 && !sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        }
    }
}