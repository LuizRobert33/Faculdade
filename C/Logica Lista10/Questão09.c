#include <stdio.h>
#include <stdlib.h>

int v_alunos[10];
float v_notas[10][4];
float soma_notas = 0;
float medias[10];
float media = 0;;
int reprovados[10];
int cont = 0;

void alunos () {

int i;

for (i = 0; i < 10; i++) {
//printf("Digite o Nº do %dº aluno: ", i + 1);
//scanf(" %d", &v_alunos[i]);
v_alunos[i] = rand () % 100;
}

}



void notas () {

int h, j;

for (h = 0; h < 10; h++) {
   
   soma_notas = 0;
   
for (j = 0; j < 4; j++) {
//printf("Digite a %dª nota do %dº aluno: ", j + 1, h + 1);
//scanf(" %d", &v_notas[h][j]);
v_notas[h][j] = (rand () % 100 ) / 10.0;
soma_notas += v_notas[h][j];
}//for

media = (float)soma_notas / 4.0;

if (media < 6) {
   reprovados[cont] = v_alunos[h];
   cont++;
}

medias[h] = media;

}//for

}



int main () {

alunos();
notas();

    int h, j;
    
    for (h = 0; h < 10; h++) {
        
        printf("Aluno %d: ", v_alunos[h]);
        
for (j = 0; j < 4; j++) {
printf("%.2f ", v_notas[h][j]);
}//for

printf("Média: %.2f\n", medias[h]);

}//for

printf("\n");
if (cont > 0) {
   
   printf("Alunos que irão fazer a recuperação: ");
   for (j = 0; j < cont; j++) {
   printf("%d, ", reprovados[j]);
   }//for
   printf("\n");
   
} else {
   printf("Nenhum aluno irá fazer recuperação\n");
}


return 0;
}