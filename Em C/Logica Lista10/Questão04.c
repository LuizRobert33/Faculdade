#include <stdio.h>

void verificar(int u, int *val){
    int d = 0;
    while (d != 2){
        u++;
        d = 0;
        for(int i = 1; i <= u; i++){
            if(u % i == 0){
                d++;
            }
        }
        if(d == 2){
            *val = u;
        }
    }
}

int main(){
    int n, prim = 0;
    scanf("%d", &n);
    verificar(n, &prim);
    printf("O primeiro num primo depois do %d é = %d\n", n, prim);
    return 0;
}