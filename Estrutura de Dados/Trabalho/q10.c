#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 32 


typedef struct Node {
    char binario[MAX_LENGTH];
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;


void initializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}


void enqueue(Queue* q, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->binario, str);
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
}


char* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    Node* temp = q->front;
    char* result = (char*)malloc(MAX_LENGTH * sizeof(char));
    strcpy(result, temp->binario);
    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return result;
}

void freeQueue(Queue* q) {
    Node* temp;
    while (q->front) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}


void generateBinaryNumbers(int n) {
    Queue q;
    initializeQueue(&q);


    enqueue(&q, "1");

    for (int i = 0; i < n; i++) {
        char* current = dequeue(&q);
        printf("%s ", current);

    
        char nextBinario[MAX_LENGTH];
        snprintf(nextBinario, MAX_LENGTH, "%s0", current);
        enqueue(&q, nextBinario);
        snprintf(nextBinario, MAX_LENGTH, "%s1", current);
        enqueue(&q, nextBinario);

        free(current);
    }

    printf("\n");
    freeQueue(&q);
}

int main() {
    int n;

    printf("Digite Um valor: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O valor deve ser maior que 0.\n");
        return 1;
    }

    generateBinaryNumbers(n);

    return 0;
}
