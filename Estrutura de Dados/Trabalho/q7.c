#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 10

typedef struct Pilha Pilha;
typedef struct Carro Carro;

Pilha *criar_Estacionamento();
Carro *criar_FilaDeEspera();

int insertCarEstac(Pilha *p, char *placa);
char *removeCarEstac(Pilha *p, Carro *c, char *placa);

int nextCarWaitLine(Carro *c, int index);

void insertCarWaitLine(Carro *c, char *placa);
char *removeCarWaitLine(Carro *c);

int carWaitLineIsFull(Carro *c);
int carWaitLineIsEmpty(Carro *c);

int carEstacIsFull(Pilha *p);
int carEstacIsEmpty(Pilha *p);

void printEstac(Pilha *p);
void printWaitLine(Carro *c);

int searchCarInEstac(Pilha *p, char *placa);

struct Pilha {
    int top;
    int size;
    char **placa;
};

struct Carro {
    int begin;
    int end;
    char **placa;
    int size;
};

int main() {
    Pilha *estacionamento = criar_Estacionamento();
    Carro *filaDeEspera = criar_FilaDeEspera();
    FILE *file = fopen("estacionamento.txt", "r");
    char operacao, placa[10];

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fscanf(file, " %c %s", &operacao, placa) != EOF) {
        if (operacao == 'E') {
            printf("ENT: %s\n", placa);
            if (insertCarEstac(estacionamento, placa) == 0) {
                insertCarWaitLine(filaDeEspera, placa);
            }
        } else if (operacao == 'S') {
            printf("SAIDA: %s\n", placa);
            removeCarEstac(estacionamento, filaDeEspera, placa);
        }

        printEstac(estacionamento);
        printWaitLine(filaDeEspera);
        printf("\n");
    }

    fclose(file);
    return 0;
}

Pilha *criar_Estacionamento() {
    Pilha *p = malloc(sizeof(Pilha));
    if (p) {
        p->top = -1;
        p->size = TAMANHO;
        p->placa = malloc(TAMANHO * sizeof(char *));
        for (int i = 0; i < TAMANHO; i++)
            p->placa[i] = malloc(10 * sizeof(char));
        return p;
    }
    return NULL;
}

Carro *criar_FilaDeEspera() {
    Carro *c = malloc(sizeof(Carro));
    if (c) {
        c->end = -1;
        c->begin = -1;
        c->size = TAMANHO;
        c->placa = malloc(TAMANHO * sizeof(char *));
        for (int i = 0; i < TAMANHO; i++)
            c->placa[i] = malloc(10 * sizeof(char));
        return c;
    }
    return NULL;
}

int insertCarEstac(Pilha *p, char *placa) {
    if (p) {
        if (!carEstacIsFull(p)) {
            p->top++;
            strcpy(p->placa[p->top], placa);
            return 1;
        } else {
            printf("!!Lotado!!\n");
            return 0;
        }
    }
    return 0;
}

char *removeCarEstac(Pilha *p, Carro *c, char *placa) {
    char *carRemoved = malloc(10 * sizeof(char));
    if (p) {
        if (!carEstacIsEmpty(p)) {
            if (strcmp(p->placa[p->top], placa) == 0) {
                p->top--;
                if (!carWaitLineIsEmpty(c)) {
                    strcpy(carRemoved, removeCarWaitLine(c));
                    insertCarEstac(p, carRemoved);
                }
                return placa;
            } else {
                if (searchCarInEstac(p, placa) == 0) {
                    if (!carWaitLineIsEmpty(c)) {
                        strcpy(carRemoved, removeCarWaitLine(c));
                        insertCarEstac(p, carRemoved);
                    }
                    return placa;
                }
            }
        }
    }
    return NULL;
}

int nextCarWaitLine(Carro *c, int index) {
    if (c) {
        return (index + 1) % c->size;
    }
    return 0;
}

void insertCarWaitLine(Carro *c, char *placa) {
    int next;
    if (c) {
        if (!carWaitLineIsFull(c)) {
            if (carWaitLineIsEmpty(c)) {
                c->begin = c->end = 0;
                strcpy(c->placa[c->begin], placa);
            } else {
                next = nextCarWaitLine(c, c->end);
                strcpy(c->placa[next], placa);
                c->end = next;
            }
        }
    }
}

char *removeCarWaitLine(Carro *c) {
    int next;
    char *aux = malloc(10 * sizeof(char));
    if (c) {
        if (!carWaitLineIsEmpty(c)) {
            strcpy(aux, c->placa[c->begin]);
            strcpy(c->placa[c->begin], "\0");
            if (c->begin == c->end) {
                c->begin = c->end = -1;
            } else {
                next = nextCarWaitLine(c, c->begin);
                c->begin = next;
            }
            printf("!!Retira um da fila!!\n");
            return aux;
        }
    }
    return NULL;
}

void printEstac(Pilha *p) {
    printf("EST: ");
    if (p && !carEstacIsEmpty(p)) {
        for (int i = 0; i <= p->top; i++) {
            printf("%s ", p->placa[i]);
        }
    }
    printf("\n");
}

void printWaitLine(Carro *c) {
    printf("FIL: ");
    if (c && !carWaitLineIsEmpty(c)) {
        int i = c->begin;
        while (i != c->end) {
            printf("%s ", c->placa[i]);
            i = nextCarWaitLine(c, i);
        }
        printf("%s ", c->placa[c->end]);
    }
    printf("\n");
}

int carWaitLineIsFull(Carro *c) {
    return c->begin == nextCarWaitLine(c, c->end);
}

int carWaitLineIsEmpty(Carro *c) {
    return c->begin == -1;
}

int carEstacIsFull(Pilha *p) {
    return p->top == p->size - 1;
}

int carEstacIsEmpty(Pilha *p) {
    return p->top == -1;
}
