/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <math.h>


void calculaHexagono(float L, float *area, float *perimetro);

int main() {
    float lado, area, perimetro;

    printf("Digite o comprimento do lado do hexágono: ");
    scanf("%f", &lado);

    
    calculaHexagono(lado, &area, &perimetro);

    printf("Área do hexágono: %.2f\n", area);
    printf("Perímetro do hexágono: %.2f\n", perimetro);

    return 0;
}


void calculaHexagono(float L, float *area, float *perimetro) {
   
    *area = (3 * sqrt(3) * L * L) / 2;

    
    *perimetro = 6 * L;
}