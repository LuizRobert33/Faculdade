//Projeto de Cadastro de time
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximo_times 10
#define maximo_jogadores 18
#define minimo_jogadores 11
#define estrangeiros 3

typedef struct {
    char nome[50];
    int estrangeiro;
} Jogador;

typedef struct {
    char nome_campeonato[50];
    char nome_time[50];
    Jogador jogadores[maximo_jogadores];
    int numero_jogadores;
    int numero_estrangeiros;
} Time;

void adicionarJogador(Time *time) {
    int contador = time->numero_jogadores + 1;
    if (contador <= maximo_jogadores) {
        printf("Informe o nome do o jogador: ", contador);
        scanf("%s", time->jogadores[time->numero_jogadores].nome);

        printf("O jogador e estrangeiro? (1 para sim, 0 para nao): ");
        scanf("%d", &time->jogadores[time->numero_jogadores].estrangeiro);

        if (time->jogadores[time->numero_jogadores].estrangeiro) {
            time->numero_estrangeiros++;
            if (time->numero_estrangeiros > estrangeiros) {
                printf("Erro: Muitos jogadores estrangeiros. Por favor, tente novamente.\n");
                time->numero_estrangeiros--;
            } else {
                time->numero_jogadores++;
            }
        } else {
            time->numero_jogadores++;
        }
    } else {
        printf("Erro: Muitos jogadores. Nao e possivel cadastrar mais jogadores.\n");
    }
}

void cadastrarTime(Time *times, int *num_times) {
    if (*num_times < maximo_times) {
        if (*num_times == 0) {
            
            printf("Informe o nome do campeonato: ");
            scanf("%s", times[*num_times].nome_campeonato);
        }

        printf("Informe o nome do time: ");
        scanf("%s", times[*num_times].nome_time);

        times[*num_times].numero_jogadores = 0;
        times[*num_times].numero_estrangeiros = 0;

        int opcao;
        do {
            adicionarJogador(&times[*num_times]);
            printf("Deseja adicionar outro jogador? (1 para sim, 0 para nao): ");
            scanf("%d", &opcao);
        } while (opcao);

        if (times[*num_times].numero_jogadores < minimo_jogadores || times[*num_times].numero_jogadores > maximo_jogadores) {
            printf("Erro: O time deve ter entre %d e %d jogadores. Seu time tem menos que isso entao nao sera possivel registralo no torneio.\n", minimo_jogadores, maximo_jogadores);
            
            *num_times -= 1;
        } else {
            (*num_times)++;
        }
    } else {
        printf("Erro: Muitos times. Nao e possivel cadastrar mais times.\n");
    }
}

void salvar(Time *times, int num_times) {
    FILE *arquivo = fopen("times.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_times; i++) {
        fprintf(arquivo, "Campeonato: %s\n", times[i].nome_campeonato);
        fprintf(arquivo, "Time: %s\n", times[i].nome_time);

        for (int j = 0; j < times[i].numero_jogadores; j++) {
            fprintf(arquivo, "Jogador: %s - %s\n",
                    times[i].jogadores[j].nome,
                    times[i].jogadores[j].estrangeiro ? "Estrangeiro" : "Brasileiro");
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void mostrarTimes(Time *times, int num_times) {
    printf("\nLista de Times:\n");
    for (int i = 0; i < num_times; i++) {
        printf("Competicao: %s\n", times[i].nome_campeonato);
        printf("Time: %s\n", times[i].nome_time);
        printf("Numero de jogadores: %d\n\n", times[i].numero_jogadores);
    }
}

int main() {
    printf("BEM VINDO AO PROGRAMA PARA CRIAR E CADASTRAR TIMES NA SUA PROPRIA COMPETICAO. DIVIRTA-SE\n");
    printf("Vamos a Regras:\n");
    printf("1 - voce pode cadastra no maximo 10 equipes\n");
    printf("2 - Cada equipe pode ter no minimo 11 jogadores e no maximo 18.\n");
    printf("3 - cada equipe pode ter no maximo 3 jogadores estrageiros.\n");
    printf("4 - em caso de mais de 3 jogadores estrageiros o Usuario podera tentar cadastra novamente um jogador com tanto que esse nao seja estrageiro.\n");
    Time times[maximo_times];
    int num_times = 0;

    int opcao;
    do {
        cadastrarTime(times, &num_times);
        printf("Deseja cadastrar outro time? (1 para sim, 0 para nao): ");
        scanf("%d", &opcao);
    } while (opcao);


    salvar(times, num_times);

    return 0;
}
