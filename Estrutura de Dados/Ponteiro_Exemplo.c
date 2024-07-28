#include <stdio.h>

int main() {
    int x = 10;     // Variável inteira
    int *ptr = &x;  // Ponteiro para um inteiro que armazena o endereço de x

    // Acessa o valor de x através do ponteiro
    printf("Valor de x: %d\n", x);     // Saída: 10
    printf("Valor de x (usando ponteiro): %d\n", *ptr); // Saída: 10

    // Acessa o endereço de x e o valor do ponteiro
    printf("Endereço de x: %p\n", &x); // Exibe o endereço de x
    printf("Valor do ponteiro (endereço de x): %p\n", ptr); // Exibe o endereço de x

    // Modifica o valor de x através do ponteiro
    *ptr = 20;
    printf("Novo valor de x: %d\n", x); // Saída: 20

    return 0;
}
