#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "graph_lists.h"
#include "graph_matrix.h"


void printPath(int currentVertex, int pred[]) {
    if (pred[currentVertex] != -1) {
        printPath(pred[currentVertex], pred);
        printf(" -> ");
    }
    printf("%d", currentVertex);
}

void printSptResults(const char* graphType, int V, int src, int dist[], int pred[]) {
    printf("\n*** Resultados de Dijkstra para %s (Origem: %d) ***\n", graphType, src);
    printf("--------------------------------------------------\n");
    printf("Vértice | Distância Mínima | Caminho\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("   %d    | ", i);
        if (dist[i] == INT_MAX) {
            printf("  Inalcançável   | N/A\n");
        } else {
            printf("       %2d        | ", dist[i]);
            printPath(i, pred);
            printf("\n");
        }
    }
    printf("--------------------------------------------------\n\n");
}


int main() {
    int V = 6;
    int src = 0;

   
    printf("=============================================\n");
    printf("      ATUALIZANDO A BIBLIOTECA GRAPHlists\n");
    printf("=============================================\n");
    GraphLists* g_list = GL_createGraph(V);
    GL_addEdge(g_list, 0, 1, 5);
    GL_addEdge(g_list, 0, 2, 3);
    GL_addEdge(g_list, 1, 3, 6);
    GL_addEdge(g_list, 1, 2, 2);
    GL_addEdge(g_list, 2, 4, 4);
    GL_addEdge(g_list, 2, 5, 2);
    GL_addEdge(g_list, 2, 3, 7);
    GL_addEdge(g_list, 3, 4, -1); 
    GL_addEdge(g_list, 4, 5, 1);
    
   
    GL_addEdge(g_list, 3, 4, 1); 

    GL_printGraph(g_list);

    int dist_list[V];
    int pred_list[V];
    GL_sptDijkstra(g_list, src, dist_list, pred_list);
    printSptResults("GRAPHlists", V, src, dist_list, pred_list);
    GL_destroyGraph(g_list);


    printf("\n=============================================\n");
    printf("      ATUALIZANDO A BIBLIOTECA GRAPHmatrix\n");
    printf("=============================================\n");
    GraphMatrix* g_matrix = GM_createGraph(V);
 
    GM_addEdge(g_matrix, 0, 1, 5);
    GM_addEdge(g_matrix, 0, 2, 3);
    GM_addEdge(g_matrix, 1, 3, 6);
    GM_addEdge(g_matrix, 1, 2, 2);
    GM_addEdge(g_matrix, 2, 4, 4);
    GM_addEdge(g_matrix, 2, 5, 2);
    GM_addEdge(g_matrix, 2, 3, 7);
    GM_addEdge(g_matrix, 3, 4, 1);
    GM_addEdge(g_matrix, 4, 5, 1);

    GM_printGraph(g_matrix);

    int dist_matrix[V];
    int pred_matrix[V];
    GM_sptDijkstra(g_matrix, src, dist_matrix, pred_matrix);
    printSptResults("GRAPHmatrix", V, src, dist_matrix, pred_matrix);
    GM_destroyGraph(g_matrix);

    return 0;
}