// Questão 01
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int V;       
    int A;       
    int **adj;   
} *Graph;

static int **MATRIXint(int r, int c, int val) {
    int **m = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        m[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++)
            m[i][j] = val;
    }
    return m;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint(V, V, 0);
    return G;
}

void GRAPHinsertArc(Graph G, int v, int w) {
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

// Função que constrói a grade dirigida m x n
Graph GRAPHrandDiGrid(int m, int n) {
    int V = m * n;
    Graph G = GRAPHinit(V);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int v = i * n + j;
            // arco horizontal
            if (j < n - 1)
                GRAPHinsertArc(G, v, v + 1);
            // arco vertical
            if (i < m - 1)
                GRAPHinsertArc(G, v, v + n);
        }
    }
    return G;
}

// Função para imprimir a matriz de adjacência
void GRAPHshow(Graph G) {
    for (int v = 0; v < G->V; v++) {
        printf("%d:", v);
        for (int w = 0; w < G->V; w++) {
            if (G->adj[v][w])
                printf(" %d", w);
        }
        printf("\n");
    }
}

int main() {
    Graph G = GRAPHrandDiGrid(3, 3);
    GRAPHshow(G);
    return 0;
}

// Questão 02
/*
Instâncias extremas — análise da função GRAPHreach(G, s, t):

1. Caso s == t:
   - A função funciona corretamente se marcar o vértice inicial como visitado
     antes de iniciar a busca.
   - Em teoria de grafos, um vértice alcança a si mesmo por um caminho de
     comprimento zero, portanto o retorno deve ser verdadeiro mesmo sem arestas.

2. Caso G->A == 0 (grafo sem arcos):
   - Se s == t → verdadeiro (caminho trivial).
   - Se s != t → falso (não há caminho possível).

3. Caso G->V == 1 (grafo com um único vértice):
   - Único vértice é o 0. Se s = t = 0 → verdadeiro.
   - Qualquer outro par (s, t) é inválido.
*/
// Questão 03






// Questão 04






// Questão 05

/*
Busca em largura a partir do vértice 0 no grafo não-dirigido dado:

Arestas:
0-1
1-2  1-4
2-3  2-4  2-9
3-4
4-5  4-6  4-7
5-6
7-8  7-9

Vizinhos (ordem crescente):
0: 1
1: 0 2 4
2: 1 3 4 9
3: 2 4
4: 1 2 3 5 6 7
5: 4 6
6: 4 5
7: 4 8 9
8: 7
9: 2 7

Resultado da BFS (num[v] = ordem de descoberta):
v:   0  1  2  3  4  5  6  7  8  9
num: 0  1  2  4  3  6  7  8  9  5

Ordem de descoberta:
0 → 1 → 2 → 4 → 3 → 9 → 5 → 6 → 7 → 8
*/

// Questão 06
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int V;
    int A;
    int **adj;
} *Graph;

int GRAPHcheckTopo(Graph G, int vv[]) {
    int *pos = malloc(G->V * sizeof(int));

    // pos[v] = posição do vértice v na permutação
    for (int i = 0; i < G->V; i++)
        pos[vv[i]] = i;

    // verifica todas as arestas
    for (int v = 0; v < G->V; v++) {
        for (int w = 0; w < G->V; w++) {
            if (G->adj[v][w] == 1) {
                if (pos[v] > pos[w]) {
                    free(pos);
                    return 0; // violou a ordem topológica
                }
            }
        }
    }

    free(pos);
    return 1; // é topológica
}
// Questão 07

#include <stdio.h>
#include <stdlib.h>

#define UNCOLORED -1

typedef struct graph {
    int V;
    int A;
    int **adj;
} *Graph;

// Função auxiliar para BFS e coloração
int bfsColoring(Graph G, int start, int *color) {
    int *queue = malloc(G->V * sizeof(int));
    int front = 0, rear = 0;

    color[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < G->V; v++) {
            if (G->adj[u][v]) { // arco u->v
                if (color[v] == UNCOLORED) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                } else if (color[v] == color[u]) {
                    free(queue);
                    return 0; // conflito: não bipartido
                }
            }
        }
    }
    free(queue);
    return 1; // componente colorida com sucesso
}

int isDirectedBipartite(Graph G, int *color) {
    for (int i = 0; i < G->V; i++)
        color[i] = UNCOLORED;

    for (int v = 0; v < G->V; v++) {
        if (color[v] == UNCOLORED) {
            if (!bfsColoring(G, v, color))
                return 0; // não bipartido
        }
    }
    return 1; // é bipartido dirigido

/*
Em caso de resposta negativa (o grafo NÃO é bipartido dirigido), o algoritmo
pode devolver como prova concreta a existência de uma aresta (u → v) cujo
color[u] == color[v], ou seja, um arco que liga dois vértices do mesmo conjunto.
Essa aresta demonstra que a bipartição não é possível, pois viola a regra
fundamental de que todos os arcos devem ir de um conjunto para o outro.

Além disso, se houver ciclos que impedem a bipartição, o algoritmo pode apontar
um ciclo com vértices da mesma cor como evidência.
*/
}


