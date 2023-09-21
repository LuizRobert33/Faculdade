#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TENTATIVA 5

int main() {
    int numero;
    int Ntentativas = 0;

    srand(time(NULL));
    numero = rand() % 100 + 1;

    printf("Tente adivinhar o número entre 1 e 100. Você tem %d tentativas.\n", TENTATIVA);

    while (1) {
        int N;
        scanf("%d", &N);
        Ntentativas++;

        if (N == numero) {
            printf("PARABÉNS! Você acertou o número (%d) em %d tentativas.\n", numero, Ntentativas);
            break;
        } else if (Ntentativas >= TENTATIVA) {
            printf("Você atingiu o limite de tentativas. O número correto era %d.\n", numero);
            break;
        } else if (N < numero) {
            printf("Digite um número maior. Tentativa %d de %d.\n", Ntentativas, TENTATIVA);
        } else {
            printf("Digite um número menor. Tentativa %d de %d.\n", Ntentativas, TENTATIVA);
        }
    }

    return 0;
}
