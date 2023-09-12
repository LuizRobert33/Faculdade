#include <stdio.h>

int main()
{
    int X[10];
    printf("Digite os Valores:\n");
    for(int i = 0; i < 10; i++){
        scanf("%d", &X[i]);
    }
    for(int i = 0; i < 10; i++){
        if(X[i] == 0 || X[i] < 0){
            X[i] = 1;
        }
        printf("%d ", X[i]); 
    }
    printf("\n"); 
    
    return 0;
}
