#include <stdio.h>
int fatorial(int vetorA[], int vetorB[]){
	int i,j=0,fat=0;
	for(i=0;i<10;i++){
		scanf("%d",&vetorA[i]);
		j=vetorA[i];
		fat=j;
		while(j>1){
			fat=fat*(j-1);
			j--;
		}
		vetorB[i]=fat;
	}
}
int main(){
	int vetA[10],vetB[10],i;
	fatorial(vetA,vetB);
	printf("FATORIAIS = \n");
	for(i=0;i<10;i++){
		printf("FATORIAl DE %d = %d \n",vetA[i],vetB[i]);
	}
	printf("\n");
}