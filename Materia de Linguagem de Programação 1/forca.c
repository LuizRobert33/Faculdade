#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 20

char* palavras[] = {"saudavel", "Uva", "desenvolvimento", "computador", "linguagem"};

int escolherPalavraA() {
    int numPalavras = sizeof(palavras) / sizeof(palavras[0]);
    return rand() % numPalavras;
}

int main() {
    srand(time(NULL)); 
    char palavraSecreta[MAX_PALAVRA];
    char forca[MAX_PALAVRA];
    int tentativas = 6;

    int indicePalavra = escolherPalavraA();
    strcpy(palavraSecreta, palavras[indicePalavra]);
    int tamanhoPalavra = strlen(palavraSecreta);

    for (int i = 0; i < tamanhoPalavra; i++) {
        forca[i] = '_';
    }
    forca[tamanhoPalavra] = '\0';

    printf("Bem-vindo ao jogo da forca!\n");

    while (tentativas > 0) {
        printf("\nPalavra: %s\n", forca);
        printf("Tentativas restantes: %d\n", tentativas);

        char letra;
        printf("Digite uma letra: ");
        scanf(" %c", &letra);

        int acertou = 0;

        for (int i = 0; i < tamanhoPalavra; i++) {
            if (palavraSecreta[i] == letra) {
                forca[i] = letra;
                acertou = 1;
            }
        }

        if (acertou == 0) {
            printf("Letra não encontrada na palavra.\n");
            tentativas--;
        }

        if (strcmp(forca, palavraSecreta) == 0) {
            printf("You Win!\n");
            break;
        }
    }

    if (tentativas == 0) {
        printf("You Lose! A palavra era: %s\n", palavraSecreta);
    }

    return 0;
}
