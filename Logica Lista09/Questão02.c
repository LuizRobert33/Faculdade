#include <stdio.h>

int main()
{
    int mat[6][3];
    int l,c, maior, menor, lme = 0, cme = 0, lma = 0, cma = 0;
    for(l = 0; l < 6; l++){
        for(c = 0; c < 3; c++){
            scanf("%d", &mat[l][c]);
        }
    }
    maior = mat[0][0];
    menor = mat[0][0];
    for(l = 0; l < 6; l++){
        for(c = 0; c < 3; c++){
            if (maior < mat[l][c]){
                maior = mat[l][c];
                lma = l+1;
                cma = c+1;
            }
            if (menor > mat[l][c]){
                menor = mat[l][c];
                lme = l+1;
                cme = c+1;
            }
        }
    }
    printf("O maior elemento é %d e esta na posição [%d][%d]\n", maior,lma,cma);
    printf("O menor elemento é %d e esta na posição [%d][%d]\n",menor,lme,cme);
    
}