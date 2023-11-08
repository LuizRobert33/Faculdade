/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Aluno {
    float nota1;
    float nota2;
    float nota3;
};

int main() {
   
   srand(time(NULL));

    struct Aluno alunos[20];

    for (int i = 0; i < 20; i++) {
        alunos[i].nota1 = rand() % 11;
        alunos[i].nota2 = rand() % 11;  
        alunos[i].nota3 = rand() % 11; 


        float media = (alunos[i].nota1 + alunos[i].nota2 + alunos[i].nota3) / 3;

        printf("Aluno %d - Notas: %.1f, %.1f, %.1f, Média: %.2f, Situação: ", i + 1,
               alunos[i].nota1, alunos[i].nota2, alunos[i].nota3, media);

        if (media >= 7.0) {
            printf("Aprovado\n");
        } else {
            printf("Reprovado\n");
        }
    }

    return 0;
}
