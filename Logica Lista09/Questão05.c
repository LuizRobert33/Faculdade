#include <stdio.h>

int main () {
    int mat[10][20];
    int vet[10];
    int l, c, soma;
    for (l = 0; l < 10; l++)
      for (c = 0; c < 20; c++){
        scanf("%d", &mat[l][c]);
      }
    for (l = 0; l < 10; l++){
        soma = 0;
        for (c = 0; c < 20; c++)
             soma = soma + mat[l][c];
        vet[l] = soma;
    }
    for (l = 0; l < 10; l++)
      for (c = 0; c < 20; c++)
           mat[l][c] =  mat[l][c] * vet[l];
    for (l = 0; l < 10; l++){
        for (c = 0; c < 20; c++)
            printf("%d", mat[l][c]);
        printf("\n");
    }
}