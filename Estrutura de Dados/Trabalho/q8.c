#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TAMANHO_GRUPO 10 
#define MAX_NUM_GRUPOS 5 

typedef struct {
    int *itens;
    int tamanho;
} Lista;


typedef struct Nodo {
    Lista lista;
    struct Nodo *proximo;
} Nodo;

typedef struct {
    Nodo *frente;
    Nodo *tras;
} Fila;


Lista criarLista(int tamanho) {
    Lista lista;
    lista.itens = (int*)malloc(tamanho * sizeof(int));
    lista.tamanho = tamanho;
    
    int i, j, unico;
    for (i = 0; i < tamanho; i++) {
        do {
            unico = 1;
            lista.itens[i] = rand() % 100; 
            for (j = 0; j < i; j++) {
                if (lista.itens[i] == lista.itens[j]) {
                    unico = 0;
                    break;
                }
            }
        } while (!unico);
    }
    return lista;
}


void inicializaFila(Fila *fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}


void adicionaFila(Fila *fila, Lista lista) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->lista = lista;
    novo->proximo = NULL;
    if (fila->tras != NULL) {
        fila->tras->proximo = novo;
    }
    fila->tras = novo;
    if (fila->frente == NULL) {
        fila->frente = novo;
    }
}

void imprimeLista(Lista lista) {
    printf("[");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%d", lista.itens[i]);
        if (i < lista.tamanho - 1) {
            printf(" ");
        }
    }
    printf("]");
}

void imprimeFila(Fila *fila) {
    Nodo *atual = fila->frente;
    while (atual != NULL) {
        imprimeLista(atual->lista);
        atual = atual->proximo;
        if (atual != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}


void liberaLista(Lista lista) {
    free(lista.itens);
}


void liberaFila(Fila *fila) {
    Nodo *atual = fila->frente;
    while (atual != NULL) {
        Nodo *temp = atual;
        atual = atual->proximo;
        liberaLista(temp->lista);
        free(temp);
    }
}

int main() {
    srand(time(NULL)); 
    Fila fila;
    inicializaFila(&fila);

   
    for (int i = 0; i < MAX_NUM_GRUPOS; i++) {
        int tamanhoGrupo = rand() % MAX_TAMANHO_GRUPO + 1;
        Lista lista = criarLista(tamanhoGrupo);
        adicionaFila(&fila, lista);
    }

    imprimeFila(&fila);

    liberaFila(&fila);

    return 0;
}
