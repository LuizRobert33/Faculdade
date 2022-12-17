#include <stdio.h>
#include <stdlib.h>
int main (){
    int mat[6][4];
    int final[6][4];
    int li[] = {0,0,0,0,0,0}, k = 0;
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 4; c++){
            mat[l][c] = rand () % 45;
            printf(" %d  ",mat[l][c]);
        }
        printf("\n");
    }
    printf("\n");
    for(int l = 0; l < 4; l++){
        li[l] = mat[l][k];
        k++;
        for(int c = 0; c < 4; c++){
            if (li[l] > mat[l][c]){
                li[l] = mat[l][c];
            }
        }
        
    }
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 4; c++){
            final[l][c] = li[l] * mat[l][c];
        }
    }
    printf("Nova matriz\n");
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 4; c++){
            printf(" %d  ", final[l][c]);
        }
        printf("\n");
    }
    
    return 0;
}