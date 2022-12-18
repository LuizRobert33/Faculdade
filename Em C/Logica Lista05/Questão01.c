#include <stdio.h>

int main (){
    
    int salario,salarioNV;

    printf("Digite o salario:\n");
    scanf("%d",&salario);

    salarioNV = (0.25*salario)+salario;

    printf("O seu novo salario e: %d\n",salarioNV);
    
    
    
    
    return 0;


}