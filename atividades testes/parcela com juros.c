#include <stdio.h>

int main(int argc, char const *argv[])
{
    int emprest,juros,parcelas,saldo;
    /*Juros de 2%*/
    printf("Digite o valor do emprestimo: \n");
    scanf("%d",&emprest);
    juros = emprest*0.2;
    saldo = juros + emprest;
    printf("o valor do emprestimo com juros e de: %d \n", saldo);
    
    
    return 0;
}
