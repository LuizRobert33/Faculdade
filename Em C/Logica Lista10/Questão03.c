#include <stdio.h>

void tabela(int n);

int main()
{
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    tabela(numero);
}

void tabela(int n){
    int cont = 2;
    printf("1\n");
    if (n > 1){
        for (int i = 2; i <= n; i++){
            for (int j = 1; j <= cont; j++){
                printf("%d ", i * j);
            }
            printf("\n");
            cont++;
        }
        
    }
}