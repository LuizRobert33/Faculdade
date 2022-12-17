#include <stdio.h>

int main()
{
    int mat[2][4];
    int i, j, np = 0, quant;
    float mpar = 0.00;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 4; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    for (i = 0; i < 2; i++){
        quant = 0;
        for (j = 0; j < 4; j++){
            if (mat[i][j] >= 12 && mat[i][j] <= 20){
                quant++;
            }
            if(mat[i][j] % 2 == 0){
                mpar += mat[i][j];
                np++;
            }
        }
        printf("Na linha %d ha %d elementos entre 12 e 20\n", i+1, quant);
    }
    mpar= mpar/np;
    printf("A media dos elementos pares da matriz é: %.2f\n",mpar);

    return 0;
}