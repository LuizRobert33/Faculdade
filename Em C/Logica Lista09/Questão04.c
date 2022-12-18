#include <stdio.h>
#include <stdlib.h>

int main(){
    float m[12][4], Tmes, Tsemana, Tano = 0;
    char mes[12][12] = {{"Janeiro"}, {"Fevereiro"}, {"Março"}, {"Abril"}, {"Maio"},
                    {"Junho"}, {"Julho"}, {"Agosto"}, {"Setembro"}, 
                    {"Outubro"}, {"Novembro"}, {"Dezembro"}};
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 4; j++){
            m[i][j] = 300 + rand() % 200 + (float) (rand() % 301) / 300; 
        }
    }
    printf("\nMatriz das vendas: \n");
    for (int i = 0; i < 12; i++){
        printf("| ");
        for (int j = 0; j < 4; j++){
            printf("%6.2f | ", m[i][j]); 
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 12; i++){
        Tmes = 0;
        for (int j = 0; j < 4; j++){
            Tmes += m[i][j];
        }
        Tano += Tmes;
        printf("Total de vendas no mês de %s: R$ %7.2f\n", mes[i], Tmes);
        
    }
    printf("\n");
    for (int j = 0; j < 4; j++){
        Tsemana = 0;
        for (int i = 0; i < 12; i++){
            Tsemana += m[i][j];
        }
        printf("Total de vendas na semana %d: R$ %7.2f\n", j + 1, Tsemana);
    }
    printf("\nTotal de vendas no ano: R$ %7.2f\n", Tano);

}