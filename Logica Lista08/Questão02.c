#include <stdio.h>

int main() {
   int vetor[10],i,cont,numero,achou;
   for (i=0;i<10;i++){
    printf("Digite os numeros:\n");
       scanf("%d",&vetor[i]);
   }
   for (cont=0;cont<5;cont++){
    printf("Digite os numeros que deseja achar:\n");
       scanf("%d",&numero);
       
   } for (i=0;i<10;i++){
       if(numero ==vetor[i]){
           achou=1;
       }
   }
   if (achou=1){
       printf("%d existe no vetor \n",numero);
   } else {
        printf("Não existe no vetor");  
   }
       
   
   
   
   
   
    return 0;
}
