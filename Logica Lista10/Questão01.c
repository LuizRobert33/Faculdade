#include <stdio.h>
#include <math.h>

float volume(float raio, float pi) {
    pi = 3,14;
    float v = 4 / 3 * (pi * pow(raio, 3));
    return v;
}

int main () {
    float raio, resultado;
    printf("Digite o raio de uma esfera para calcular o seu volume: ");
    scanf("%f", &raio);
    resultado = volume * raio;
    printf("%.3f", resultado);
    return 0;
}