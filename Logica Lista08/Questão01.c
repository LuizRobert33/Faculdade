#include <stdio.h>
int main(){
    
    int vet[10];
    int cont = 0;
    int N=0;
    for(int i=0;i<10;i++){
        printf("Digite o numero:\n");
        scanf("%d",&vet[i]);
    }
    for(int i=0;i<10;i++){
        if(vet[i]<0){
            cont++;
        }
        else if(vet[i]>0){
            N = N + vet[i];
        }
        
    }
    printf("Tem %d numeros negativos\n",cont);
    printf("a soma dos numeros positivos e: %d\n",N);
    
    return 0;

}