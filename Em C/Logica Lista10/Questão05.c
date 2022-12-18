#include <stdio.h>

int operacao(int a, int b, char o);


int main()
{
    int a, b, resultado;
    char o;
    printf("Digite dois números: ");
    scanf(" %d %d", &a, &b);
    printf("Digite a operação [+ ou *]: ");
    scanf(" %c", &o);
    resultado = operacao(a, b, o);
    printf("%d %c %d = %d\n", a, o, b, resultado);
}

int operacao(int a, int b, char o)
{
    int res;
    if (o == '+'){
        res = a + b;
    }
    if (o == '*'){
        res = a * b;
    }
    return res;
}



