#include <stdio.h>

void soma(int a, int b){
    int resultado = a+b;
    printf("%d\n",resultado);
}

int main(){
    soma(2,5);
    soma(5,20);
    soma(10,10);
    return 0;
}