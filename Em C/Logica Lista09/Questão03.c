#include <stdio.h>
#include <stdlib.h>

int main()
{
    float nota[15][5], mediaA, mediaC, somaA, somaC = 0;
    int situacao = 0;
    char nome[15][20];
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 5; j++){
            nota[i][j] = 1 + rand() % 9 + (float) (rand() % 11) / 10;
        }
    }
    printf("Matriz das notas: \n");
    for (int i = 0; i < 15; i++){
        printf("| ");
        for (int j = 0; j < 5; j++){
            printf("%.1f | ", nota[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 15; i++){
        printf("Nome do aluno %d: ", i + 1);
        scanf(" %[^\n]", nome[i]);
    }
    printf("\n");
    for (int i = 0; i < 15; i++){
        somaA = 0;
        for (int j = 0; j < 5; j++){
            somaA += nota[i][j];
        }
        mediaA = somaA / 5.0;
        somaC += mediaA;
        if (mediaA >= 7){
            situacao = 1;
        }
        if (mediaA < 4){
            situacao = -1;
        }
        printf("Aluno %d: %s, Média: %.1f, Situação: ", i + 1, nome[i], mediaA);
        switch (situacao)
        {
            case 1:
                printf("Aprovado\n");
                break;
            case -1:
                printf("Reprovado\n");
                break;
            default:
                printf("Exame\n");
                break;
        }
    }
    mediaC = somaC / 15;
    printf("\nMédia da classe: %.1f\n", mediaC);
}