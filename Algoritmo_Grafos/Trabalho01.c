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

3-4 -> retorno
0-5 -> avanço
5-3 -> árvore
4-1 -> cruzado





