//Escrever maior Valor
#include <stdio.h>

int main(){
    int N1,N2;
    printf("Digite 2 numeros: \n");
    scanf("%d%d",&N1,&N2);
    if (N1>N2)
    {
        printf(" o %d e o maior numero",N1);
    } else{
        printf("o %d e o maior numero",N2);
    }
    return 0;
}