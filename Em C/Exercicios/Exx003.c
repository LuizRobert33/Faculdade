//Sucessor e Antecessor do Numero
#include <stdio.h>
int main(){
    int N1,sucessor,antecessor;
    printf("Digite um numero: ");
    scanf("%d",&N1);
    sucessor = N1+1;
    antecessor = N1 - 1;
    printf("Voce digitou o numero: %d. Seu sucessor e: %d e seu antecessor e:%d",N1,sucessor,antecessor);
    return 0;
}