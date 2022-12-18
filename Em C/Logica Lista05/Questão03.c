#include <stdio.h>
#include <math.h>

int main(){


    int N,Nquadrado,Ncubo;
    float Nraizq,Nraizc;
    printf("Digite o Numero:\n");
    scanf("%d",&N);

    Nquadrado = N*N;
    Ncubo = N*N*N;
    Nraizq = sqrt(N);
    Nraizc = cbrt(N);

    printf("o quadrado de %d e:%d\n",N,Nquadrado);
    printf("o cubico de %d e:%d\n",N,Ncubo);
    printf("a raiz quadrada de %d e:%0.f\n",N,Nraizq);
    printf("a raiz cubica de %d e: %0.2f\n",N,Nraizc);

}