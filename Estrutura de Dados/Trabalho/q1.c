#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Bombas representam o valor 0 neste jogo!
typedef struct Pilha{
	int tamanho, topo;
	int *itens;
}Pilha;

Pilha *criar_Pilha(int tamanho);
int inserir_Pilha(Pilha *pilha, int valor);
int verificar_Pilha(Pilha *pilha, int valor);
int pilha_vazia(Pilha *pilha);
int pilha_cheia(Pilha *pilha);
int mover_casas(Pilha *pilha, int valor);
void imprimir_Pilha(Pilha *pilha);

int main(){
	srand(time(NULL));

	int dado, bomba, vitoria = 0;
	int turno = 0;

	Pilha *jogador1 = criar_Pilha(15);
	Pilha *jogador2 = criar_Pilha(15);

	for(dado = jogador1->tamanho; dado >= 0; dado--){

		bomba = rand() % jogador1->tamanho / 5; //chance pela metade do n° de casas
		if(bomba == 0 && dado > 3){
			inserir_Pilha(jogador1, bomba);
			inserir_Pilha(jogador2, bomba);
		}

		else{
			inserir_Pilha(jogador1, dado);
			inserir_Pilha(jogador2, dado);
		}
	}

	while(1){
		printf("Jogo do Tabuleiro!\n");

		if(turno == 0){ //vez do jogador 1
			printf("=============Vez do Jogador 1=============\n");
			
			imprimir_Pilha(jogador1);

			printf("pressione Enter para rolar o dado!\n\n\n");
			scanf("%*c");

			dado = (rand() % 6) + 1;

			printf("Voce tirou o numero %d\n\n", dado);
			
			vitoria = mover_casas(jogador1, dado);
			if(vitoria == 1){
				printf("Parabens voce ganhou jogador 1!\n");
				break;
			}
			
			turno = 1;
			imprimir_Pilha(jogador1);
		}
		else if(turno == 1){ //vez do jogador 2
			printf("=============Vez do Jogador 2=============\n");
			
			imprimir_Pilha(jogador2);
			
			printf("pressione Enter para rolar o dado!\n\n\n");
			scanf("%*c");

			dado = (rand() % 6) + 1;

			printf("Voce tirou o numero %d\n\n", dado);

			vitoria = mover_casas(jogador2, dado);
			if(vitoria == 1){
				printf("Parabens voce ganhou jogador 2!\n");
				break;
			}
			turno = 0;
			imprimir_Pilha(jogador2);
		
		}		

		printf("\nPressione Enter para seguir proximo turno!");
		scanf("%*c");

		system("clear");

	}
}

Pilha *criar_Pilha(int tamanho){
	Pilha *pilha = malloc(sizeof(Pilha));
	if(pilha){
		pilha->tamanho = tamanho;
		pilha->topo = -1;
		pilha->itens = malloc(tamanho * sizeof(int));
	}
	return pilha;
}

int inserir_Pilha(Pilha *pilha, int valor){
	if(pilha){
		if(!pilha_cheia(pilha)){
			pilha->topo++;
			pilha->itens[pilha->topo] = valor;
		}
	}
}

int mover_casas(Pilha *pilha, int valor){
	int i = 0;

	if(pilha){
		if(pilha->topo < valor){
			return 1; //ganhou o jogo
		}

		else if(pilha->itens[pilha->topo - valor] != 0){ //verificar se pisou numa bomba
			if(pilha->topo > valor){
				pilha->topo = pilha->topo - valor;
			}
		}

		else{
			printf("voce pisou em uma bomba!\n");
			while(1){
				if(pilha_cheia(pilha) || i == 3){
					break;
				}
				pilha->topo = pilha->topo + i;
				i++;
			}
		}
	}

	return 0;
}

void imprimir_Pilha(Pilha *pilha){

	int i = 0;
	if(pilha && !pilha_vazia(pilha)){
	
		printf("-> ");

		for(i = pilha->topo; i >= 0; i--){
			if(pilha->itens[i] == 0)
				printf(" \U0001F4A3 ");
			
			else if(i == pilha->topo)
				printf(" '%d' ", pilha->itens[i]);

			else
				printf(" %d ", pilha->itens[i]);
		}
	}
	printf("<-\n");
}

int pilha_cheia(Pilha *pilha){
	if(pilha){
		return pilha->topo == (pilha->tamanho - 1);
	}
}

int pilha_vazia(Pilha *pilha){
	if(pilha){
		return pilha->topo == -1;
	}
}
