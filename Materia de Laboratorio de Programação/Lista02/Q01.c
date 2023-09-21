#include <stdio.h>

int main()
{
    int P[5];
    int cont50 = 0;
    int cont = 0;
    float M;
    for(int i = 0; i<5; i++){
        scanf("%d",&P[i]);
        cont = cont+P[i];
        if(P[i]<50){
            cont50++;
        }
    M = cont/5;     
    }
    printf("Tem %d produtos com preço menor que 50\n",cont50);
    printf("A media dos produtos e: %0.2f",M);
    
    

    return 0;
}
