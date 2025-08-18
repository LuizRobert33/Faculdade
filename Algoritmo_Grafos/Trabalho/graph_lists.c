#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph_lists.h"


static Node* createNode(int v, int w) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

GraphLists* GL_createGraph(int V) {
    GraphLists* graph = malloc(sizeof(GraphLists));
    graph->numVertices = V;
    graph->adjLists = malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void GL_destroyGraph(GraphLists* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}

void GL_addEdge(GraphLists* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void GL_printGraph(GraphLists* graph) {
    printf("Representação do Grafo (Listas de Adjacências):\n");
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Vértice %d: ", v);
        while (temp) {
            printf("-> (%d, peso %d) ", temp->vertex, temp->weight);
            temp = temp->next;
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

void GL_sptDijkstra(GraphLists* graph, int src, int dist[], int pred[]) {
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

        Node* crawler = graph->adjLists[u];
        while (crawler != NULL) {
            int v = crawler->vertex;
            int weight = crawler->weight;

            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
            crawler = crawler->next;
        }
    }
}