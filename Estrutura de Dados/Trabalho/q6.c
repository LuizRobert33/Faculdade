#include <stdio.h>
#include <stdlib.h>


typedef struct Pilha {
    int topo;
    int capacidade;
    int *itens;
} Pilha;


Pilha *criar_pilha(int capacidade) {
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->itens = malloc(capacidade * sizeof(int));
    return pilha;
}

int pilha_vazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilha_cheia(Pilha *pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

void empilhar(Pilha *pilha, int item) {
    if (!pilha_cheia(pilha)) {
        pilha->itens[++pilha->topo] = item;
    }
}

int desempilhar(Pilha *pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->itens[pilha->topo--];
    }
    return -1; 
}

void liberar_pilha(Pilha *pilha) {
    free(pilha->itens);
    free(pilha);
}

// Função para encontrar o menor fator primo
int menor_fator_primo(int n) {
    if (n % 2 == 0) return 2;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return i;
    }
    return n; // n é primo
}

// Função para fatorar o número
void fatoracao_prima(int n) {
    Pilha *pilha = criar_pilha(100);
    int original_n = n;

    while (n > 1) {
        int fator = menor_fator_primo(n);
        empilhar(pilha, fator);
        n /= fator;
    }

    printf("%d = ", original_n);

    while (!pilha_vazia(pilha)) {
        printf("%d", desempilhar(pilha));
        if (!pilha_vazia(pilha)) {
            printf(" * ");
        }
    }
    printf("\n");

    liberar_pilha(pilha);
}

int main() {
    int n;

    printf("Digite um numero inteiro maior que 1: ");
    scanf("%d", &n);

    if (n > 1) {
        fatoracao_prima(n);
    } else {
        printf("O numero deve ser maior que 1.\n");
    }

    return 0;
}
