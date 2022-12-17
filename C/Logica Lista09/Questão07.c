#include <stdio.h>
#include <stdlib.h>
int main (){
    int mat[4][4];
    int lso[] = {0,0,0,0}, cso[] = {0,0,0,0}, k, dp = 0, ds = 0, cont = 0;
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 4; c++){
            mat[l][c] = 4;
            printf(" %d  ",mat[l][c]);
        }
        printf("\n");
    }
    k = 4;
    for(int l = 0; l < 4; l++){
        k--;
        for(int c = 0; c < 4; c++){
            lso[l] += mat[l][c];
            if (l == c){
                dp += mat[l][c];
            }
            if (c == k){
                ds += mat[l][c];
            }
            
        }
        
    }
    for(int c = 0; c < 4; c++){
        for(int l = 0; l < 4; l++){
            cso[c] += mat[l][c];
        }
    }
    for(int i = 0; i < 4; i++){
        if (lso[i] == cso[i] && lso[i] == dp && lso[i] == ds)
            cont++;
    }
    if(cont == 4)
        printf("A matriz é um quadrado mágico");
    else
        printf("A matriz não é um quadrado mágico");
    return 0;
}