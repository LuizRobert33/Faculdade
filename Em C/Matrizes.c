#include <stdio.h>

int main(int argc, char const *argv[])
{
    int mat [5] [5],linha,coluna;

    for(linha=0;linha<4;linha++){
        for(coluna=0;coluna<4;coluna++){
            printf("Informe o elemento de [%d, %d]",linha,coluna);
            scanf("%d",&mat[linha][coluna]);
            

        }
    }
    for(linha=0;linha<4;linha++){
        for(coluna=0;coluna<4;coluna++){
            printf("%d",mat[linha][coluna]);
        }
    }



    return 0;
}
