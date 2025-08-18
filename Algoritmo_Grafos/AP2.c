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
#include <stdio.h>
#include <stdlib.h>


#define NUM_NODES 8 


int get_index(int label, const int labels[]) {
    for (int i = 0; i < NUM_NODES; i++) {
        if (labels[i] == label) {
            return i;
        }
    }
    return -1; 
}


int get_label(int index, const int labels[]) {
    if (index >= 0 && index < NUM_NODES) {
        return labels[index];
    }
    return -1; 
}


void resolver_questao3() {
    printf("----------------------------------------\n");
    printf("Resolvendo a Questão 3\n");
    printf("----------------------------------------\n\n");

   
    const int labels[NUM_NODES] = {2, 3, 5, 7, 8, 9, 10, 11};

    
    int edges[][2] = {
        {7, 11}, {7, 8},
        {5, 11}, {5, 8},
        {3, 8}, {3, 10},
        {11, 2}, {11, 9}, {11, 10},
        {8, 9}
    };
    int num_edges = sizeof(edges) / sizeof(edges[0]);

    
    int adj[NUM_NODES][NUM_NODES] = {0};
    int in_degree[NUM_NODES] = {0};

    
    for (int i = 0; i < num_edges; i++) {
        int u_label = edges[i][0];
        int v_label = edges[i][1];
        int u_idx = get_index(u_label, labels);
        int v_idx = get_index(v_label, labels);

        if (u_idx != -1 && v_idx != -1 && adj[u_idx][v_idx] == 0) {
            adj[u_idx][v_idx] = 1;
            in_degree[v_idx]++;
        }
    }

    
    int queue[NUM_NODES];
    int front = 0, rear = 0;

    
    for (int i = 0; i < NUM_NODES; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int topo_order_indices[NUM_NODES];
    int count = 0;

    while (front < rear) {
        int u_idx = queue[front++];
        topo_order_indices[count++] = u_idx;

        
        for (int v_idx = 0; v_idx < NUM_NODES; v_idx++) {
            if (adj[u_idx][v_idx] == 1) {
                
                in_degree[v_idx]--;
                
                if (in_degree[v_idx] == 0) {
                    queue[rear++] = v_idx;
                }
            }
        }
    }

    if (count != NUM_NODES) {
        printf("Erro: O grafo contém um ciclo! A ordenação topológica não é possível.\n");
        return;
    }

  
    printf("1. Permutação Topológica:\n");
    for (int i = 0; i < NUM_NODES; i++) {
        printf("%d ", get_label(topo_order_indices[i], labels));
    }
    printf("\n\n");


    printf("2. Numeração Topológica (Vértice -> Número):\n");
    int topo_numbering[12] = {0}; 
    for (int i = 0; i < NUM_NODES; i++) {
         int label = get_label(topo_order_indices[i], labels);
         topo_numbering[label] = i;
         printf("%d -> %d\n", label, i);
    }
    printf("\n");

    
    printf("3. Permutação Anti-topológica:\n");
    for (int i = NUM_NODES - 1; i >= 0; i--) {
        printf("%d ", get_label(topo_order_indices[i], labels));
    }
    printf("\n\n");

    
    printf("4. Numeração Anti-topológica (Vértice -> Número):\n");
    for (int i = 0; i < NUM_NODES; i++) {
        int label = get_label(topo_order_indices[i], labels);
        int anti_topo_num = NUM_NODES - 1 - topo_numbering[label];
        printf("%d -> %d\n", label, anti_topo_num);
    }
    printf("\n");
}





// Questão 04
/*
#include <stdio.h

    
    int pre[] = {0, 1, 5, 4, 2, 3};
    
    int post[] = {4, 0, 5, 1, 3, 2};

    
    int arcos[][2] = {
        {3, 4},
        {0, 5},
        {5, 3},
        {4, 1}
    };
    int num_arcos = sizeof(arcos) / sizeof(arcos[0]);

    printf("Classificação dos arcos com base nos tempos da DFS:\n\n");

    for (int i = 0; i < num_arcos; i++) {
        int u = arcos[i][0];
        int v = arcos[i][1];

        printf("Analisando o arco %d -> %d:\n", u, v);

        
        int pre_u = pre[u];
        int post_u = post[u];
        int pre_v = pre[v];
        int post_v = post[v];

        printf("  (pre[%d]=%d, post[%d]=%d), (pre[%d]=%d, post[%d]=%d)\n", u, pre_u, u, post_u, v, pre_v, v, post_v);

        
        if (pre_u < pre_v && post_v < post_u) {
            printf("  -> Classificação: Aresta de Árvore ou Avanço (Tree/Forward Edge)\n\n");
        } else if (pre_v < pre_u && post_u < post_v) {
            printf("  -> Classificação: Aresta de Retorno (Back Edge)\n\n");
        } else if (post_v < pre_u || post_u < pre_v) {
            printf("  -> Classificação: Aresta de Cruzamento (Cross Edge)\n\n");
        } else {
            
            printf("  -> Classificação: Indeterminada (dados anômalos)\n\n");
        }
    }
}



*/





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


