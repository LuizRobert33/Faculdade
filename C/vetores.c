#include <stdio.h>
int main(int argc, char const *argv[])
{
    int vetor[10],numero,cont,posnumero = -1;
    for(cont=0;cont<10;cont++){
        printf("informe o valor: %d",cont);
        scanf("%d",&vetor[cont]); 
    }

    printf("informe um numero para pesquisar no vetor: ");
    scanf("%d",&numero);

    for(cont=0;cont<10;cont++){
        if(vetor[cont]==numero){
            posnumero = cont; 
            break;
        }
    }
    if(posnumero>= 0){
        printf("o valor do indice e %d",posnumero);

    } else {
        printf("false");
    }


    return 0;
}
