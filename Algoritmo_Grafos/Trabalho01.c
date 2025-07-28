//01 questão
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 7 

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adj[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int post[MAX_VERTICES]; 
    int time; 
} Graph;


Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}


void addEdge(Graph* graph, int src, int dest) {
    
    Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;

    
    newNode = createNode(src);
    newNode->next = graph->adj[dest];
    graph->adj[dest] = newNode;
}


void initGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adj[i] = NULL;
        graph->visited[i] = 0;
        graph->post[i] = -1; 
    }
    graph->time = 0;
}


void DFS(Graph* graph, int v) {
    graph->visited[v] = 1;

    Node* temp = graph->adj[v];
    
    if (v > 0 && !graph->visited[v - 1]) {
        DFS(graph, v - 1);
    }
    if (v < MAX_VERTICES - 1 && !graph->visited[v + 1]) {
        DFS(graph, v + 1);
    }

    graph->post[v] = graph->time++; 
}


void GRAPHdfs_path(Graph* graph) {
    printf("Aplicando GRAPHdfs() ao grafo caminho 0-1-2-3-4-5-6 (partindo de 0):\n");
    DFS(graph, 0); // Inicia a DFS do vértice 0

    printf("Vetor post[] produzido:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("post[%d] = %d\n", i, graph->post[i]);
    }
    printf("\n");
}

int main() {
    Graph graph;
    initGraph(&graph);

    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 5, 6);


    GRAPHdfs_path(&graph);


    initGraph(&graph); 
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 5, 6);

    DFS(&graph, 3); 

    printf("Vetor post[] produzido com inicio em 3:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("post[%d] = %d\n", i, graph.post[i]);
    }
    printf("\n");

    return 0;
}
//02 questão
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct Graph {
    int numVertices;
    Node** adjLists; 
    bool* visited;    
    int* postOrder; 
    int postOrderIndex;
} Graph;


Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    graph->postOrder = (int*)malloc(vertices * sizeof(int));
    graph->postOrderIndex = 0;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}


void addEdge(Graph* graph, int v1, int v2) {
    Node* newNode = createNode(v2);
    Node* current = graph->adjLists[v1];
    Node* prev = NULL;

    while (current != NULL && current->vertex < v2) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) { 
        newNode->next = graph->adjLists[v1];
        graph->adjLists[v1] = newNode;
    } else {
        newNode->next = current;
        prev->next = newNode;
    }
}


void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    graph->postOrder[graph->postOrderIndex++] = vertex;
}

void performDFS(Graph* graph) {
 
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            DFS(graph, i);
        }
    }
}


void printAdjLists(Graph* graph) {
    printf("Listas de Adjacencia:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("  %c: ", 'a' + i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf("%c -> ", 'a' + temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
   
    int numVertices = 8; 
    Graph* graph = createGraph(numVertices);


    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 0, 6);


    addEdge(graph, 1, 3); 
    addEdge(graph, 1, 5); 


    addEdge(graph, 6, 2); 

    addEdge(graph, 3, 2); 
    addEdge(graph, 3, 4); 

    
    addEdge(graph, 5, 4); 

    
    addEdge(graph, 2, 7); 


    addEdge(graph, 4, 7); 

    printf("Grafo criado com %d vertices.\n", numVertices);

    printAdjLists(graph);

    printf("\nIniciando Busca em Profundidade (DFS):\n");
    performDFS(graph);

    printf("\nPermutacao dos vertices em pos-ordem (a=0, b=1, ...):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%c ", 'a' + graph->postOrder[i]);
    }
    printf("\n");

    for (int i = 0; i < numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph->postOrder);
    free(graph);

    return 0;
}
//03° questão
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Node {
    int vertexIndex; 
    struct Node* next;
} Node;


typedef struct Graph {
    int numVertices;
    Node** adjLists;     
    bool* visited;      
    int* preOrder;      
    int* postOrder;    
    int time;            
    int* vertexValues;  
    int* valueToIndexMap; 
    int maxValue;       
} Graph;


Node* createNode(int vIndex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertexIndex = vIndex;
    newNode->next = NULL;
    return newNode;
}


Graph* createGraph(int numVertices, int* initialVertexValues) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));
    graph->visited = (bool*)malloc(numVertices * sizeof(bool));
    graph->preOrder = (int*)malloc(numVertices * sizeof(int));
    graph->postOrder = (int*)malloc(numVertices * sizeof(int));
    graph->time = 1; 

   
    graph->maxValue = 0;
    for (int i = 0; i < numVertices; i++) {
        if (initialVertexValues[i] > graph->maxValue) {
            graph->maxValue = initialVertexValues[i];
        }
    }
    
    graph->valueToIndexMap = (int*)malloc((graph->maxValue + 1) * sizeof(int));
    for (int i = 0; i <= graph->maxValue; i++) {
        graph->valueToIndexMap[i] = -1; 
    }

    graph->vertexValues = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
        graph->preOrder[i] = 0;
        graph->postOrder[i] = 0;
        graph->vertexValues[i] = initialVertexValues[i];
        graph->valueToIndexMap[initialVertexValues[i]] = i; 
    }
    return graph;
}


void addEdge(Graph* graph, int v1_value, int v2_value) {
    int v1_index = graph->valueToIndexMap[v1_value];
    int v2_index = graph->valueToIndexMap[v2_value];

    if (v1_index == -1 || v2_index == -1) {
        printf("Erro: Tentativa de adicionar aresta com valor de vertice nao mapeado.\n");
        return;
    }

    Node* newNode = createNode(v2_index);
    newNode->next = graph->adjLists[v1_index]; 
    graph->adjLists[v1_index] = newNode;
}


void DFS(Graph* graph, int vertexIndex) {
    graph->visited[vertexIndex] = true;
    graph->preOrder[vertexIndex] = graph->time++;

    
    Node* temp = graph->adjLists[vertexIndex];
    while (temp != NULL) {
        int connectedVertexIndex = temp->vertexIndex;
        if (!graph->visited[connectedVertexIndex]) {
            DFS(graph, connectedVertexIndex);
        }
        temp = temp->next;
    }

    
    graph->postOrder[vertexIndex] = graph->time++;
}

void calculateOrders(Graph* graph) {

    int startVertices[] = {7, 5, 3};
    int numStartVertices = sizeof(startVertices) / sizeof(startVertices[0]);

    for (int i = 0; i < numStartVertices; i++) {
        int startVertexValue = startVertices[i];
        int startVertexIndex = graph->valueToIndexMap[startVertexValue];
        if (startVertexIndex != -1 && !graph->visited[startVertexIndex]) {
            DFS(graph, startVertexIndex);
        }
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            DFS(graph, i);
        }
    }
}

void printOrders(Graph* graph) {
    printf("Numeracoes em Pre-Ordem e Pos-Ordem:\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertice %d (indice %d):\n", graph->vertexValues[i], i);
        printf("  Pre-Ordem: %d\n", graph->preOrder[i]);
        printf("  Pos-Ordem: %d\n", graph->postOrder[i]);
        printf("-------------------------------------\n");
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph->preOrder);
    free(graph->postOrder);
    free(graph->vertexValues);
    free(graph->valueToIndexMap);
    free(graph);
}

int main() {
    
    int initialVertexValues[] = {2, 3, 5, 7, 8, 9, 10, 11};
    int numVertices = sizeof(initialVertexValues) / sizeof(initialVertexValues[0]);

    Graph* graph = createGraph(numVertices, initialVertexValues);


    addEdge(graph, 7, 11);
    addEdge(graph, 7, 8);
    addEdge(graph, 5, 11);
    addEdge(graph, 5, 9);
    addEdge(graph, 3, 8);
    addEdge(graph, 3, 10);
    addEdge(graph, 11, 2);
    addEdge(graph, 11, 9);
    addEdge(graph, 11, 10);
    addEdge(graph, 8, 10);
    addEdge(graph, 9, 2);

    printf("Grafo criado. Calculando numeracoes...\n\n");

    calculateOrders(graph);

    printOrders(graph);

    freeGraph(graph);

    return 0;
}
// 04º questão

 void classificaArcos(Graph G){

    for (int v = 0; v < G->V ; ++v){
      for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;

        if (pre[v] < pre[w] && post[v] > post[w] && pa[w] == v)
          printf("%d-%d árvore\n", v, w);

        else if (pre[v] < pre[w] && post[v] > post[w])
          printf("%d-%d avanço\n", v, w);

        else if (pre[v] > pre[w] && post[v] < post[w])
          printf("%d-%d retorno\n", v, w);

        else
          printf("%d-%d cruzado\n", v, w);
    }
  }
}



// 05º questão

char ident[100];

void GRAPHdfs(Graph G) {
    cnt = cntt = 0;
    ident[0] = '\0';

    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            pa[v] = v;
            printf("%d-dfsR(G,%d)\n", v, v);
            ident[0] = '\0';
            dfsR(G, v);
        }
    }
}

static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;

    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;

        printf("%s%d-%d", ident, v, w);

        if (pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            pa[w] = v;

            strcat(ident, " . ");
            dfsR(G, w);

            ident[strlen(ident) - 3] = '\0';
        } else {
            printf("\n");
        }
    }

    post[v] = cntt++;

    printf("%s%d\n", ident, v);
}



//06º questão
/*

3-4 -> retorno
0-5 -> avanço
5-3 -> árvore
4-1 -> cruzado

*/
// 07º questão



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estruturas para grafo por listas de adjacência
typedef struct AdjNode {
    int vertex;
    struct AdjNode* next;
} AdjNode;

typedef struct GraphDFS {
    int numVertices;
    AdjNode** adjLists;
    int* pre;    // ordem de pré-visita
    int* post;   // ordem de pós-visita
    int* pa;     // pai na árvore DFS
    int cnt;     // contador de pré-visita
    int cntt;    // contador de pós-visita
    char ident[100];
} GraphDFS;

// Criação do grafo
GraphDFS* createGraphDFS(int vertices) {
    GraphDFS* graph = (GraphDFS*)malloc(sizeof(GraphDFS));
    graph->numVertices = vertices;
    graph->adjLists = (AdjNode**)malloc(vertices * sizeof(AdjNode*));
    graph->pre = (int*)malloc(vertices * sizeof(int));
    graph->post = (int*)malloc(vertices * sizeof(int));
    graph->pa = (int*)malloc(vertices * sizeof(int));
    graph->cnt = 0;
    graph->cntt = 0;
    graph->ident[0] = '\0';
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->pre[i] = -1;
        graph->post[i] = -1;
        graph->pa[i] = -1;
    }
    return graph;
}

// Adiciona aresta direcionada
void addEdgeDFS(GraphDFS* graph, int src, int dest) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Função recursiva auxiliar
void dfsR(GraphDFS* G, int v) {
    G->pre[v] = G->cnt++;
    AdjNode* temp = G->adjLists[v];
    while (temp != NULL) {
        int w = temp->vertex;
        printf("%s%d-%d", G->ident, v, w);
        if (G->pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            G->pa[w] = v;
            strcat(G->ident, " . ");
            dfsR(G, w);
            G->ident[strlen(G->ident) - 3] = '\0';
        } else {
            printf("\n");
        }
        temp = temp->next;
    }
    G->post[v] = G->cntt++;
    printf("%s%d\n", G->ident, v);
}

// Função principal de DFS
void GRAPHdfs(GraphDFS* G) {
    G->cnt = G->cntt = 0;
    G->ident[0] = '\0';
    for (int v = 0; v < G->numVertices; ++v)
        G->pre[v] = -1;
    for (int v = 0; v < G->numVertices; ++v) {
        if (G->pre[v] == -1) {
            G->pa[v] = v;
            printf("%d-dfsR(G,%d)\n", v, v);
            G->ident[0] = '\0';
            dfsR(G, v);
        }
    }
}

// Função para liberar memória
void freeGraphDFS(GraphDFS* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        AdjNode* current = graph->adjLists[i];
        while (current != NULL) {
            AdjNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjLists);
    free(graph->pre);
    free(graph->post);
    free(graph->pa);
    free(graph);
}
 // 08° questão
 #include <stdio.h>
#include <stdlib.h>

#define N 10 // número máximo de vértices (0 a 9)

void bfs(int adj[N][N], int n, int start) {
    int num[N];
    int fila[N];
    int ini = 0, fim = 0;
    int ordem[N];
    int ordem_idx = 0;

    for (int i = 0; i < n; i++) num[i] = -1;

    num[start] = 0;
    fila[fim++] = start;
    ordem[ordem_idx++] = start;

    int passo = 1;
    while (ini < fim) {
        int v = fila[ini++];
        for (int w = 0; w < n; w++) {
            if (adj[v][w] && num[w] == -1) {
                num[w] = passo++;
                fila[fim++] = w;
                ordem[ordem_idx++] = w;
            }
        }
    }

    printf("Vetor num[]:\n");
    for (int i = 0; i < n; i++) {
        printf("num[%d] = %d\n", i, num[i]);
    }

    printf("\nOrdem de descoberta dos vértices:\n");
    for (int i = 0; i < ordem_idx; i++) {
        printf("%d ", ordem[i]);
    }
    printf("\n");
}

int main() {
    int n = 10; // vértices de 0 a 9
    int adj[N][N] = {0};

    // Adicionando as arestas do enunciado (grafo não-dirigido)
    int arestas[][2] = {
        {0,1}, {1,2}, {1,4}, {2,3}, {2,4}, {2,9}, {3,4},
        {4,5}, {4,6}, {4,7}, {5,6}, {7,8}, {7,9}
    };
    int m = sizeof(arestas)/sizeof(arestas[0]);
    for (int i = 0; i < m; i++) {
        int u = arestas[i][0], v = arestas[i][1];
        adj[u][v] = adj[v][u] = 1;
    }

    printf("Busca em largura a partir do vértice 0:\n");
    bfs(adj, n, 0);

    return 0;
}
// 09° questão
#include <stdio.h>
#include <stdlib.h>

#define N 100 // ajuste conforme o máximo de vértices do seu grafo

void GRAPHbfs(int adj[N][N], int n, int start, int num[N]) {
    int fila[N];
    int ini = 0, fim = 0;
    for (int i = 0; i < n; i++) num[i] = -1;

    num[start] = 0;
    fila[fim++] = start;
    int passo = 1;

    while (ini < fim) {
        int v = fila[ini++];
        for (int w = 0; w < n; w++) {
            if (adj[v][w] && num[w] == -1) {
                num[w] = passo++;
                fila[fim++] = w;
            }
        }
    }
}
// 10° questão

/*
Não, uma árvore de busca em largura não será sempre um subgrafo gerador. Um subgrafo gerador é um subgrafo que contém todos os vértices do grafo original. No entanto, durante uma busca em largura, partindo de um vértice v, pode acontecer de nem todos os vértices serem alcançáveis a partir de v, especialmente se o grafo for não conexo (em grafos não direcionados) ou não fortemente conectado (em grafos direcionados).
*/


