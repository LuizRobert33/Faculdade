// 01
#include <stdio.h>
#include <stdlib.h>

#define N 7 // número de vértices

int adj[N][N]; // matriz de adjacência
int visited[N];
int post[N];
int cnt = 0;

void GRAPHinsertEdge(int v, int w) {
    adj[v][w] = 1;
    adj[w][v] = 1; // grafo não direcionado
}

void dfs(int v) {
    visited[v] = 1;
    for (int w = 0; w < N; w++) {
        if (adj[v][w] && !visited[w]) {
            dfs(w);
        }
    }
    post[v] = cnt++;
}

void GRAPHdfs() {
    for (int v = 0; v < N; v++) visited[v] = 0;
    cnt = 0;
    for (int v = 0; v < N; v++) {
        if (!visited[v]) dfs(v);
    }
}

int main() {
    // Monta o grafo caminho: 0-1 1-2 2-3 3-4 4-5 5-6
    GRAPHinsertEdge(0, 1);
    GRAPHinsertEdge(1, 2);
    GRAPHinsertEdge(2, 3);
    GRAPHinsertEdge(3, 4);
    GRAPHinsertEdge(4, 5);
    GRAPHinsertEdge(5, 6);

    GRAPHdfs();

    printf("Vetor post[]:\n");
    for (int v = 0; v < N; v++) {
        printf("post[%d] = %d\n", v, post[v]);
    }

    return 0;
}