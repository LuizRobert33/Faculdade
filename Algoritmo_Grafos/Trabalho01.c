//01
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
//02
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
//03



