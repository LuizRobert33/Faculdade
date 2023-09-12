#include <stdio.h>

int main()
{
    int N[10];
    printf("Digite seu valor de entrada:\n");
    for(int i = 0; i < 10; i++){ 
        scanf("%d", &N[i]);
    }
    for(int i = 0; i < 10; i++){ 
        N[i] = N[i] * 2;
    }
    for(int i = 0; i < 10; i++){
        printf("%d ", N[i]);
    }

    return 0;
}
