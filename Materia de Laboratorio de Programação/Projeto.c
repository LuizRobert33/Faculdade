//Projeto registro de um time no Campeonato
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 6
#define MAX_JOGADORES 18
#define MAX_JOGADORES_ESTRANGEIROS 3

typedef struct {
    char nome[50];
    int estrangeiro;
} Jogador;

typedef struct {
    char nome_campeonato[50];
    char nome_time[50];
    Jogador jogadores[MAX_JOGADORES];
    int num_jogadores;
    int num_estrangeiros;
} Time;

void adicionarJogador(Time *time) {
    if (time->num_jogadores < MAX_JOGADORES) {
        printf("Informe o nome do jogador: ");
        scanf("%s", time->jogadores[time->num_jogadores].nome);

        printf("O jogador é estrangeiro? (1 para sim, 0 para não): ");
        scanf("%d", &time->jogadores[time->num_jogadores].estrangeiro);

        if (time->jogadores[time->num_jogadores].estrangeiro) {
            time->num_estrangeiros++;
            if (time->num_estrangeiros > MAX_JOGADORES_ESTRANGEIROS) {
                printf("Erro: Muitos jogadores estrangeiros. Por favor, tente novamente.\n");
                time->num_estrangeiros--;
            } else {
                time->num_jogadores++;
            }
        } else {
            time->num_jogadores++;
        }
    } else {
        printf("Erro: Muitos jogadores. Por favor, tente novamente.\n");
    }
}

void cadastrarTime(Time *times, int *num_times) {
    if (*num_times < MAX_TIMES) {
        printf("Informe o nome do campeonato: ");
        scanf("%s", times[*num_times].nome_campeonato);

        printf("Informe o nome do time: ");
        scanf("%s", times[*num_times].nome_time);

        times[*num_times].num_jogadores = 0;
        times[*num_times].num_estrangeiros = 0;

        int opcao;
        do {
            adicionarJogador(&times[*num_times]);
            printf("Deseja adicionar outro jogador? (1 para sim, 0 para não): ");
            scanf("%d", &opcao);
        } while (opcao);

        (*num_times)++;
    } else {
        printf("Erro: Muitos times. Não é possível cadastrar mais times.\n");
    }
}

void salvarEmArquivo(Time *times, int num_times) {
    FILE *arquivo = fopen("times.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_times; i++) {
        fprintf(arquivo, "Campeonato: %s\n", times[i].nome_campeonato);
        fprintf(arquivo, "Time: %s\n", times[i].nome_time);

        for (int j = 0; j < times[i].num_jogadores; j++) {
            fprintf(arquivo, "Jogador: %s - %s\n",
                    times[i].jogadores[j].nome,
                    times[i].jogadores[j].estrangeiro ? "Estrangeiro" : "Local");
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

int main() {
    Time times[MAX_TIMES];
    int num_times = 0;

    int opcao;
    do {
        cadastrarTime(times, &num_times);
        printf("Deseja cadastrar outro time? (1 para sim, 0 para não): ");
        scanf("%d", &opcao);
    } while (opcao);

    salvarEmArquivo(times, num_times);

    return 0;
}
