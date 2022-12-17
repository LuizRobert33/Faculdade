#include <stdio.h>
#include <stdlib.h>
int main (){
    int mat[5][5];
    int vet[] = {0,0,0,0,0}, k;
    for(int l = 0; l < 10; l++){
        for(int c = 0; c < 20; c++){
            mat[l][c] = rand () % 5;
            printf("%d",mat[l][c]);
        }
        printf("\n");
    }
    k = 20;
    for(int l = 0; l < 10; l++){
        k -= 1;
        for(int c = 0; c < 20; c++){
            if (l == 4){
                vet[0] += mat[l][c];
            }
            if (c == 2){
                vet[1] += mat[l][c];
            }
            if (l == c){
                vet[2] += mat[l][c];
            }
            if (c == k){
                vet[3] += mat[l][c];
            }
            vet[4] += mat[l][c];
        }
        
    }
    printf("Soma dos elementos da linha 4 = %d\n", vet[0]);
    printf("Soma dos elementos da coluna 2 = %d\n", vet[1]);
    printf("Soma dos elementoa da diagonal principal = %d\n", vet[2]);
    printf("Soma dos elementos da diagonal secundária = %d\n", vet[3]);
    printf("Soma de todos os elementos da matriz = %d\n", vet[4]);
    return 0;
}