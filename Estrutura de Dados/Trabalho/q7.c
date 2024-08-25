#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE 10 // Capacidade do estacionamento

typedef struct Carro {
    char placa[8];
} Carro;

typedef struct Estacionamento {
    Carro vagas[CAPACIDADE];
    int quantidade;
} Estacionamento;

typedef struct Fila {
    Carro carros[CAPACIDADE];
    int frente, tras, tamanho;
} Fila;

// Funções do estacionamento
void inicializar_estacionamento(Estacionamento *estacionamento) {
    estacionamento->quantidade = 0;
}

int estacionamento_vazio(Estacionamento *estacionamento) {
    return estacionamento->quantidade == 0;
}

int estacionamento_cheio(Estacionamento *estacionamento) {
    return estacionamento->quantidade == CAPACIDADE;
}

void adicionar_ao_estacionamento(Estacionamento *estacionamento, Carro carro) {
    if (!estacionamento_cheio(estacionamento)) {
        estacionamento->vagas[estacionamento->quantidade] = carro;
        estacionamento->quantidade++;
    }
}

void remover_do_estacionamento(Estacionamento *estacionamento, char *placa) {
    for (int i = 0; i < estacionamento->quantidade; i++) {
        if (strcmp(estacionamento->vagas[i].placa, placa) == 0) {
            for (int j = i; j < estacionamento->quantidade - 1; j++) {
                estacionamento->vagas[j] = estacionamento->vagas[j + 1];
            }
            estacionamento->quantidade--;
            break;
        }
    }
}

void imprimir_estacionamento(Estacionamento *estacionamento) {
    printf("EST: ");
    if (estacionamento_vazio(estacionamento)) {
        printf("Vazio");
    } else {
        for (int i = 0; i < estacionamento->quantidade; i++) {
            printf("%s ", estacionamento->vagas[i].placa);
        }
    }
    printf("\n");
}

// Funções da fila
void inicializar_fila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

int fila_vazia(Fila *fila) {
    return fila->tamanho == 0;
}

int fila_cheia(Fila *fila) {
    return fila->tamanho == CAPACIDADE;
}

void enfileirar(Fila *fila, Carro carro) {
    if (!fila_cheia(fila)) {
        fila->tras = (fila->tras + 1) % CAPACIDADE;
        fila->carros[fila->tras] = carro;
        fila->tamanho++;
    }
}

Carro desenfileirar(Fila *fila) {
    Carro carro = fila->carros[fila->frente];
    fila->frente = (fila->frente + 1) % CAPACIDADE;
    fila->tamanho--;
    return carro;
}

void imprimir_fila(Fila *fila) {
    printf("FIL: ");
    if (fila_vazia(fila)) {
        printf("Vazia");
    } else {
        for (int i = 0; i < fila->tamanho; i++) {
            int index = (fila->frente + i) % CAPACIDADE;
            printf("%s ", fila->carros[index].placa);
        }
    }
    printf("\n");
}

int main() {
    Estacionamento estacionamento;
    Fila fila;
    FILE *arquivo;
    char comando;
    char placa[8];

    inicializar_estacionamento(&estacionamento);
    inicializar_fila(&fila);

    // Abrindo o arquivo de comandos
    arquivo = fopen("estacionamento.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fscanf(arquivo, " %c %7s", &comando, placa) != EOF) {
        Carro carro;
        strcpy(carro.placa, placa);

        if (comando == 'E' || comando == 'e') {
            if (estacionamento_cheio(&estacionamento)) {
                printf("!! Lotado !!\n");
                if (!fila_vazia(&fila)) {
                    printf("!! Retira um da fila !!\n");
                    Carro carro_fila = desenfileirar(&fila);
                    remover_do_estacionamento(&estacionamento, carro_fila.placa);
                }
                enfileirar(&fila, carro);
            } else {
                adicionar_ao_estacionamento(&estacionamento, carro);
            }
        } else if (comando == 'S' || comando == 's') {
            remover_do_estacionamento(&estacionamento, placa);
            if (!fila_vazia(&fila)) {
                Carro carro_fila = desenfileirar(&fila);
                adicionar_ao_estacionamento(&estacionamento, carro_fila);
            }
        }

        printf("ENT: %s\n", placa);
        imprimir_estacionamento(&estacionamento);
        imprimir_fila(&fila);
    }

    fclose(arquivo);
    return 0;
}
