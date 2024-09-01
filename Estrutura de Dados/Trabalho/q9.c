#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_FILA 100


typedef struct {
    char nome[MAX_NOME];
    int idade;
} Pessoa;


typedef struct Nodo {
    Pessoa pessoa;
    struct Nodo *proximo;
} Nodo;

typedef struct {
    Nodo *frente;
    Nodo *tras;
} Fila;




void inicializaFila(Fila *fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}


void push(Fila *fila, Pessoa pessoa) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->pessoa = pessoa;
    novo->proximo = NULL;
    if (fila->tras != NULL) {
        fila->tras->proximo = novo;
    }
    fila->tras = novo;
    if (fila->frente == NULL) {
        fila->frente = novo;
    }
}


Pessoa pop(Fila *fila) {
    if (fila->frente == NULL) {
        fprintf(stderr, "Fila vazia.\n");
        exit(EXIT_FAILURE);
    }
    Nodo *temp = fila->frente;
    Pessoa pessoa = temp->pessoa;
    fila->frente = temp->proximo;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
    return pessoa;
}


int estaVazia(Fila *fila) {
    return fila->frente == NULL;
}


void ordenarFila(Fila *fila) {
    Fila filaAux;
    inicializaFila(&filaAux);
    
    while (!estaVazia(fila)) {
        Pessoa maior = pop(fila);
        Fila filaTemp;
        inicializaFila(&filaTemp);

       
        while (!estaVazia(fila)) {
            Pessoa atual = pop(fila);
            if (atual.idade > maior.idade) {
                push(&filaTemp, maior);
                maior = atual;
            } else {
                push(&filaTemp, atual);
            }
        }

     
        push(&filaAux, maior);

       
        while (!estaVazia(&filaTemp)) {
            push(fila, pop(&filaTemp));
        }
    }

  
    while (!estaVazia(&filaAux)) {
        push(fila, pop(&filaAux));
    }
}


void carregarFila(Fila *fila, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Pessoa pessoa;
    while (fscanf(arquivo, "%s %d", pessoa.nome, &pessoa.idade) != EOF) {
        push(fila, pessoa);
    }

    fclose(arquivo);
}


void imprimirFila(Fila *fila) {
    Nodo *atual = fila->frente;
    while (atual != NULL) {
        printf("%s %d\n", atual->pessoa.nome, atual->pessoa.idade);
        atual = atual->proximo;
    }
}

int main() {
    Fila fila;
    inicializaFila(&fila);

    
    carregarFila(&fila, "name_age.txt");

   
    ordenarFila(&fila);

   
    printf("Fila ordenada pela idade (maior para menor):\n");
    imprimirFila(&fila);

    while (!estaVazia(&fila)) {
        pop(&fila); 

    return 0;
}

}