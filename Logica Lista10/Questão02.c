#include <stdio.h>

void gerar_vetor(int v[], int n);
void mostrar_vetor(int v[], int n);
int maior_numero(int v[]);
int menor_numero(int v[]);

int main()
{
    int vetor[5], maior, menor;
    gerar_vetor(vetor, 5);
    mostrar_vetor(vetor, 5);
    maior = maior_numero(vetor);
    menor = menor_numero(vetor);
    printf("\nMaior: %d\nMenor: %d\n", maior, menor);
}

void gerar_vetor(int v[], int n){
    for (int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
}
void mostrar_vetor(int v[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}
int maior_numero(int v[]){
    int maior = v[0];
    for (int i = 0; i < 5; i++){
        if (v[i] > maior){
            maior = v[i];
        }
    }
    return maior;
}
int menor_numero(int v[]){
    int menor = v[0];
    for (int i = 0; i < 5; i++){
        if (v[i] < menor){
            menor = v[i];
        }
    }
    return menor;
}