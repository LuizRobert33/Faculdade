// Compilar gcc -std=c99 -Wall ppp.c qqq.c -o xxx
// Compilar gcc main.c lista.c ou matriz.c
//

#include "lista.h"
//#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

	Graph H;
	vertex v, w, A, V;

	printf("Qtd de Vertices: \n");
	scanf("%d", &V);
	H = GRAPHinit(V);

	printf("Qtd de Arcos: \n");
	scanf("%d", &A);

	for (int i = 0; i < A; i++){
		printf("Insira o Arco %d (v-w): \n", i+1 );
		scanf("%d-%d", &v, &w);
		GRAPHinsertArc(H, v, w);
	}

	printf("É grafo topológico? %d\n", topol(H));
}
