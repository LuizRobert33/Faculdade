// Senha valida
#include <stdio.h>
int main(){
    int senha = 1234,N;
    printf("\nDigite a senha\n");
    scanf("%d",&N);
    if (N==senha)
    {
        printf("\nACESSO PERMITIDO\n");
    } else{
        printf("\nACESSO NEGADO\n");
    }
    return 0;
    
}