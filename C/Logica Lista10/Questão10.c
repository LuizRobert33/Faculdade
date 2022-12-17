#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gera_vetorA(int vetorA[]){
	int i;
	srand(time(NULL));
	for(i=0;i<10;i++){
		vetorA[i]=rand()%100;
	}
}
int imprime_vetorA(int vetorA[]){
	int i;
	printf("VETOR = ");
	for(i=0;i<9;i++){
		printf("%d, ",vetorA[i]);
	}
	printf("%d\n",vetorA[9]);
}
int ordena_vetorA(int vetorA[]){
	int i,j,aux;
	/*for(i=0;i<10;i++){
		vetorB=rand();
	}*/
	for(i=0;i<10;i++){
		for(j=i;j<10;j++){
			if(vetorA[i]>vetorA[j]){
				aux=vetorA[i];
				vetorA[i]=vetorA[j];
				vetorA[j]=aux;
			}
		}
	}
	printf("VETOR ORDENADO = ");
	for(i=0;i<9;i++){
		printf("%d, ",vetorA[i]);
	}
	printf("%d\n",vetorA[9]);
}
int main(){
	int vetA[10],vetB[10];
	gera_vetorA(vetA);
	imprime_vetorA(vetA);
	ordena_vetorA(vetA);
}