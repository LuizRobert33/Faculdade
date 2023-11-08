/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>

struct dados {
     unsigned int matricula: 8;
     unsigned int sexo: 8 ;
     unsigned  int rendimento: 8;
    unsigned  int Primeira: 8;
};

int main() {
    
    struct dados c;

    printf("Tamanho da estrutura dados: %ld bytes\n", sizeof(c));


    return 0;
}