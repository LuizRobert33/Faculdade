#include <stdio.h>
int main(int argc, char const *argv[])
{
    int g1,g2,gols;
    printf("----TIME A X TIME B----\n");
    printf("Digite o Numero de gols do time A: \n");
    scanf("%d",&g1);
    printf("Digite o Numero de gols do time B: \n");
    scanf("%d",&g2);
    gols = g1 - g2;
    if(gols = 1){
        printf("PLACAR NORMAL");
    } else if (gols = 2){
        pritnf("PLACAR NORMAL");
    } else if(gols = 0){
        printf("JOGO EMPATADO");
    } else{
        printf("GOLEADA");
    }

    return 0;
}
