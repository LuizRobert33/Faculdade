// Questão 04
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

typedef struct No {
    int vertice;
    struct No* proximo;
} No;


typedef struct Grafo {
    int num_vertices;
    No** listas_adj; 
} Grafo;


No* criar_no(int v) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->vertice = v;
    novo_no->proximo = NULL;
    return novo_no;
}


Grafo* criar_grafo(int V) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->num_vertices = V;
    grafo->listas_adj = (No**)malloc(V * sizeof(No*));

    for (int i = 0; i < V; i++) {
        grafo->listas_adj[i] = NULL;
    }
    return grafo;
}


void adicionar_aresta(Grafo* grafo, int v1, int v2) {
   
    No* novo_no = criar_no(v2);
    novo_no->proximo = grafo->listas_adj[v1];
    grafo->listas_adj[v1] = novo_no;

    novo_no = criar_no(v1);
    novo_no->proximo = grafo->listas_adj[v2];
    grafo->listas_adj[v2] = novo_no;
}


void bfs_caminhos_minimos(Grafo* grafo, int s, int dist[], int pred[]) {
    int V = grafo->num_vertices;

    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX; 
        pred[i] = -1;      
    }

  
    dist[s] = 0;

    int* fila = (int*)malloc(V * sizeof(int));
    int frente = 0, tras = 0;
    fila[tras++] = s;

  
    while (frente != tras) {
        
        int u = fila[frente++];

        
        No* temp = grafo->listas_adj[u];
        while (temp != NULL) {
            int v = temp->vertice;

         
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1; 
                pred[v] = u;           
                fila[tras++] = v;      
            }
            temp = temp->proximo;
        }
    }
    free(fila); 
}


void imprimir_caminho(int s, int v, int pred[]) {
    if (v == s) {
        printf("%d", s);
    } else if (pred[v] == -1) {
        printf("Nenhum caminho de %d para %d", s, v);
    } else {
        imprimir_caminho(s, pred[v], pred);
        printf(" -> %d", v);
    }
}

void imprimir_resultados(Grafo* grafo, int s, int dist[], int pred[]) {
    printf("Resultados a partir da origem %d:\n", s);
    printf("----------------------------------\n");
    printf("Vértice | Distância | Caminho Mínimo\n");
    printf("----------------------------------\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("   %d    |     %d     | ", i, dist[i]);
        imprimir_caminho(s, i, pred);
        printf("\n");
    }
    printf("----------------------------------\n");
}



int main() {
    int V = 8;
    Grafo* g = criar_grafo(V);

  
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 3);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 3, 7);
    adicionar_aresta(g, 4, 5);
    adicionar_aresta(g, 4, 6);
    adicionar_aresta(g, 4, 7);
    adicionar_aresta(g, 5, 6);
    adicionar_aresta(g, 6, 7);

    int s = 0; 

    int dist[V];
    int pred[V];


    bfs_caminhos_minimos(g, s, dist, pred);

    
    imprimir_resultados(g, s, dist, pred);

    return 0;
}

// Questão 05

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include <stdbool.h> 

typedef struct Grafo {
    int num_vertices;
    int** matriz_adj; 
} Grafo;


Grafo* criar_grafo(int V) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->num_vertices = V;

    
    grafo->matriz_adj = (int**)malloc(V * sizeof(int*));
    
    for (int i = 0; i < V; i++) {
        grafo->matriz_adj[i] = (int*)malloc(V * sizeof(int));
        
        for (int j = 0; j < V; j++) {
            grafo->matriz_adj[i][j] = 0;
        }
    }
    return grafo;
}


void adicionar_aresta(Grafo* grafo, int origem, int destino, int peso) {
    if (origem < grafo->num_vertices && destino < grafo->num_vertices) {
        grafo->matriz_adj[origem][destino] = peso;
    }
}


int encontrar_min_distancia(int dist[], bool visitado[], int V) {
    int min = INT_MAX, min_indice = -1;

    for (int v = 0; v < V; v++) {
        if (visitado[v] == false && dist[v] <= min) {
            min = dist[v];
            min_indice = v;
        }
    }
    return min_indice;
}


void dijkstra_matriz_spt(Grafo* grafo, int s, int dist[], int pred[]) {
    int V = grafo->num_vertices;
    bool visitado[V]; 
    
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
        visitado[i] = false;
    }

    
    dist[s] = 0;

    
    for (int count = 0; count < V - 1; count++) {
        
        int u = encontrar_min_distancia(dist, visitado, V);

        
        if (u == -1) break;

        
        visitado[u] = true;

        
        for (int v = 0; v < V; v++) {
          
            if (!visitado[v] && grafo->matriz_adj[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + grafo->matriz_adj[u][v] < dist[v])
            {
                dist[v] = dist[u] + grafo->matriz_adj[u][v];
                pred[v] = u;
            }
        }
    }
}



void imprimir_caminho(int s, int v, int pred[]) {
    if (v == s) {
        printf("%d", s);
    } else if (pred[v] == -1) {
        printf("Nenhum caminho de %d para %d", s, v);
    } else {
        imprimir_caminho(s, pred[v], pred);
        printf(" -> %d", v);
    }
}

void imprimir_resultados(Grafo* grafo, int s, int dist[], int pred[]) {
    printf("Resultados de Dijkstra a partir da origem %d:\n", s);
    printf("--------------------------------------------------\n");
    printf("Vértice | Distância Mínima | Caminho\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("   %d    |        %d         | ", i, (dist[i] == INT_MAX ? -1 : dist[i]));
        imprimir_caminho(s, i, pred);
        printf("\n");
    }
    printf("--------------------------------------------------\n");
}



int main() {
    int V = 6;
    Grafo* g = criar_grafo(V);

    
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 1, 1);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 6);
    adicionar_aresta(g, 4, 5, 3);

    int s = 0; 

    int dist[V];
    int pred[V];

    
    dijkstra_matriz_spt(g, s, dist, pred);

    
    imprimir_resultados(g, s, dist, pred);

    
    for (int i = 0; i < V; i++) {
        free(g->matriz_adj[i]);
    }
    free(g->matriz_adj);
    free(g);

    return 0;
}



