//Projeto registro de times em um campeonato
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 6
#define MAX_JOGADORES 18
#define MIN_JOGADORES 11
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

        printf("O jogador e estrangeiro? (1 para sim, 0 para nao): ");
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
        printf("Erro: Muitos jogadores. Nao e possivel cadastrar mais jogadores.\n");
    }
}

void cadastrarTime(Time *times, int *num_times) {
    if (*num_times < MAX_TIMES) {
        if (*num_times == 0) {
            // Solicitar o nome do campeonato apenas no primeiro time
            printf("Informe o nome do campeonato: ");
            scanf("%s", times[*num_times].nome_campeonato);
        }

        printf("Informe o nome do time: ");
        scanf("%s", times[*num_times].nome_time);

        times[*num_times].num_jogadores = 0;
        times[*num_times].num_estrangeiros = 0;

        int opcao;
        do {
            adicionarJogador(&times[*num_times]);
            printf("Deseja adicionar outro jogador? (1 para sim, 0 para nao): ");
            scanf("%d", &opcao);
        } while (opcao);

        if (times[*num_times].num_jogadores < MIN_JOGADORES || times[*num_times].num_jogadores > MAX_JOGADORES) {
            printf("Erro: O time deve ter entre %d e %d jogadores. Seu time tem menos que isso entao nao sera possivel registralo no torneio.\n", MIN_JOGADORES, MAX_JOGADORES);
            // Reiniciar o contador de times para que esse não seja contabilizado
            *num_times -= 1;
        } else {
            (*num_times)++;
        }
    } else {
        printf("Erro: Muitos times. Nao e possivel cadastrar mais times.\n");
    }
}

void salvarEmArquivo(Time *times, int num_times) {
    FILE *arquivo = fopen("times.txt", "w");
    if (arquivo == NULL) {
       
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

void mostrarListaTimes(Time *times, int num_times) {
    printf("\nLista de Times:\n");
    for (int i = 0; i < num_times; i++) {
        printf("Competicao: %s\n", times[i].nome_campeonato);
        printf("Time: %s\n", times[i].nome_time);
        printf("Numero de jogadores: %d\n\n", times[i].num_jogadores);
    }
}

int main() {
    Time times[MAX_TIMES];
    int num_times = 0;

    int opcao;
    do {
        cadastrarTime(times, &num_times);
        printf("Deseja cadastrar outro time? (1 para sim, 0 para nao): ");
        scanf("%d", &opcao);
    } while (opcao);

    mostrarListaTimes(times, num_times);
    salvarEmArquivo(times, num_times);

    return 0;
}
