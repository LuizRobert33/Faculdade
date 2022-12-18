#include <stdio.h>
int main(int argc, char const *argv[])
{
    int V,D,E,Vfinal,Vempates,Vderrotas,pontos;
    printf("Digite o numero da vitoria: \n");
    scanf("%d",&V);
    printf("Digite o numero de empates: \n");
    scanf("%d",&E);
    printf("Digite o numero de derrotas: \n");
    scanf("%d",&D);
    Vfinal = V*3;
    Vempates = E*1;
    Vderrotas = D*0;
    pontos = Vfinal + Vempates + Vderrotas;
    if(pontos>=45){
        printf("Seu time fez %d pontos em 38 rodadas e não foi rebaixado\n",pontos);

    } else{
       printf("Seu time fez %d pontos em 38 rodadas e foi rebaixado\n",pontos);
    }
    
    return 0;
}
