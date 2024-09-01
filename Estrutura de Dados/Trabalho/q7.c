#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAGAS 10
#define MAX_PLACA 8

typedef struct {
    char placa[MAX_PLACA];
} Carro;

typedef struct {
    Carro carros[MAX_VAGAS];
    int topo;
} Estacionamento;

typedef struct Node {
    Carro carro;
    struct Node* prox;
} Node;

typedef struct {
    Node* frente;
    Node* tras;
} Fila;

// Funções de inicialização
void inicializaEstacionamento(Estacionamento* est) {
    est->topo = -1;
}

void inicializaFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

// Funções para estacionamento
int estacionamentoCheio(Estacionamento* est) {
    return est->topo == MAX_VAGAS - 1;
}

int estacionamentoVazio(Estacionamento* est) {
    return est->topo == -1;
}

void entraEstacionamento(Estacionamento* est, Carro carro) {
    if (!estacionamentoCheio(est)) {
        est->topo++;
        est->carros[est->topo] = carro;
    }
}

void saiEstacionamento(Estacionamento* est, Carro* carro) {
    if (!estacionamentoVazio(est)) {
        *carro = est->carros[est->topo];
        est->topo--;
    }
}

// Funções para fila
void entraFila(Fila* fila, Carro carro) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->carro = carro;
    novo->prox = NULL;
    if (fila->tras != NULL) {
        fila->tras->prox = novo;
    }
    fila->tras = novo;
    if (fila->frente == NULL) {
        fila->frente = novo;
    }
}

void saiFila(Fila* fila, Carro* carro) {
    if (fila->frente != NULL) {
        Node* temp = fila->frente;
        *carro = temp->carro;
        fila->frente = fila->frente->prox;
        if (fila->frente == NULL) {
            fila->tras = NULL;
        }
        free(temp);
    }
}

int filaVazia(Fila* fila) {
    return fila->frente == NULL;
}

// Funções de impressão
void printEstac(Estacionamento* est) {
    printf("EST: ");
    if (!estacionamentoVazio(est)) {
        for (int i = 0; i <= est->topo; i++) {
            printf("%s ", est->carros[i].placa);
        }
    }
    printf("\n");
}

void printWaitLine(Fila* fila) {
    printf("FIL: ");
    Node* atual = fila->frente;
    while (atual != NULL) {
        printf("%s ", atual->carro.placa);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    Estacionamento est;
    Fila fila;
    inicializaEstacionamento(&est);
    inicializaFila(&fila);

    FILE *file = fopen("estacionamento.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char acao;
    char placa[MAX_PLACA];

    while (fscanf(file, " %c %s", &acao, placa) != EOF) {
        if (acao == 'E') {
            printf("ENT: %s\n", placa);
            Carro carro;
            strcpy(carro.placa, placa);
            if (estacionamentoCheio(&est)) {
                printf("!!Lotado!!\n");
                entraFila(&fila, carro);
            } else {
                entraEstacionamento(&est, carro);
            }
        } else if (acao == 'S') {
            printf("SAIDA: %s\n", placa);
            Carro carroSaindo;
            saiEstacionamento(&est, &carroSaindo);
            if (!filaVazia(&fila)) {
                Carro carroEntrando;
                saiFila(&fila, &carroEntrando);
                printf("!!Retira um da fila!!\n");
                entraEstacionamento(&est, carroEntrando);
            }
        }
        printEstac(&est);
        printWaitLine(&fila);
    }

    fclose(file);
    return 0;
}
