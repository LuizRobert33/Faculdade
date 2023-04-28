// Solicitar idade de pessoas

#include <stdio.h>

int main() {
    int idade = 0, cont18 = 0, cont = 0;
    while (idade != -1) {
        printf("Digite uma idade: \n");
        scanf("%d", &idade);
        if (idade > 18) {
            cont18++;
        } else if (idade >= 0) {
            cont++;
        }
    }
    printf("Tem %d pessoas acima de 18 anos e %d pessoas com menos de 18 anos.", cont18, cont);
    return 0;
}
