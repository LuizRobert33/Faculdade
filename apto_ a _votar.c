#include <stdio.h>

int main (){

    char nome[20];
    int idade;

    printf("Digite seu nome\n");
    scanf("%s",nome);
    printf("Digite a sua idade\n");
    scanf("%d",&idade);

    if(idade>=16){
        printf("o senhor ou senhora %s esta apto(a) a votar ",nome);
    } else {
        printf("o senhor ou senhora %s não esta apto(a) a votar",nome);
    }
    
}