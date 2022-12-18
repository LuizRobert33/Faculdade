#include <stdio.h>

void verificar(int u){
    int vl = 1;
    printf("S = ");
    while(vl <= u){
        printf(" %d + 1 /", vl);
        vl++;
    }
    printf("\nS = %d", vl);
}

int main(){
    int s;
    scanf("%d", &s);
    verificar(s);
    return 0;
}