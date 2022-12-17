#include <stdio.h>
#include <stdlib.h>
int main(){
    int matrizA [4] [5], matrizB [5] [2];
    int x,y,produto;
    float aux=0;
    for (x=0;x<4;x++){
        for (y=0;y<5;y++){
            matrizA[x][y]= rand()%5;
            printf ("%d",matrizA[x][y]);
        }
        printf("\n");
    }
    printf ("--------------------\n");
    for (x=0;x<5;x++){
        for (y=0;y<2;y++){
        matrizB[x][y]= rand()%2;
            printf ("%d",matrizB[x][y]);
        }
        printf("\n");
    }
    printf("-----------------------\n");
    for (x=0;x<4;x++){
        for (y=0;y<2;y++){
            produto= matrizA[x][y]*matrizB[x][y];
            printf ("%d",produto);
        }
        printf ("\n");
    }

}