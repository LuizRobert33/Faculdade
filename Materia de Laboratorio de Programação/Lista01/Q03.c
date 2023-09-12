#include <stdio.h>

int main() {
    int T, N[1000];

    
    printf("Digite o valor:\n ");
    scanf("%d", &T);

    int idx = 0;
    for (int i = 0; i < 1000; i++) {
        N[i] = idx;
        idx++;
        if (idx == T) {
            idx = 0;
        }
    }

    for (int i = 0; i < 1000; i++) {
        printf("N[%d] = %d\n", i, N[i]);
    }

    return 0;
}
