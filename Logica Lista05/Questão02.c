#include <stdio.h>

int main(){

    float r = 3.14;
    float Area;
    float R;

    printf("digite o raio do circulo:\n");
    scanf("%f",&R);

    Area = r * (R*R);

    printf("A area do circulo e: %0.2f\n ",Area);
}