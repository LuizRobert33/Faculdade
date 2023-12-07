//Projeto de Cadastro de time
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 10
#define MAX_JOGADORES 18
#define MIN_JOGADORES 11
#define MAX_ESTRANGEIROS 3

typedef struct {
    char nome[50];
    int estrangeiro;
} Jogador;

typedef struct {
    char nome_campeonato[50];
    char nome_time[50];
    Jogador jogadores[MAX_JOGADORES];
    int numero_jogadores;
    int numero_estrangeiros;
} Time;

// Função para adicionar jogador a um time
void adicionarJogador(Time *time) {
    int contador = time->numero_jogadores + 1;
    if (contador <= MAX_JOGADORES) {
        printf("Informe o nome do jogador: ");
        scanf(" %[^\n]", time->jogadores[time->numero_jogadores].nome);

        printf("O jogador é estrangeiro? (1 para sim, 0 para não): ");
        scanf("%d", &time->jogadores[time->numero_jogadores].estrangeiro);

        if (time->jogadores[time->numero_jogadores].estrangeiro) {
            if (time->numero_estrangeiros < MAX_ESTRANGEIROS) {
                time->numero_estrangeiros++;
            } else {
                printf("Erro: Muitos jogadores estrangeiros. Por favor, tente novamente.\n");
                return;
            }
        }
        
        time->numero_jogadores++;
    } else {
        printf("Erro: Muitos jogadores. Não é possível cadastrar mais jogadores.\n");
    }
}

// Função para cadastrar um time
void cadastrarTime(Time *times, int *num_times) {
    if (*num_times < MAX_TIMES) {
        if (*num_times == 0) {
            printf("Informe o nome do campeonato: ");
            scanf(" %[^\n]", times[*num_times].nome_campeonato);
        }

        printf("Informe o nome do time: ");
        scanf(" %[^\n]", times[*num_times].nome_time);

        times[*num_times].numero_jogadores = 0;
        times[*num_times].numero_estrangeiros = 0;

        int opcao;
        do {
            adicionarJogador(&times[*num_times]);
            printf("Deseja adicionar outro jogador? (1 para sim, 0 para não): ");
            scanf("%d", &opcao);
        } while (opcao);

        if (times[*num_times].numero_jogadores < MIN_JOGADORES || times[*num_times].numero_jogadores > MAX_JOGADORES) {
            printf("Erro: O time deve ter entre %d e %d jogadores. Seu time tem menos que isso, então não será possível registrá-lo no torneio.\n", MIN_JOGADORES, MAX_JOGADORES);
            
            
            printf("Compile o programa novamente para poder registrar os times na competição.\n");

            exit(EXIT_FAILURE);
        } else {
            (*num_times)++;
        }
    } else {
        printf("Erro: Muitos times. Não é possível cadastrar mais times.\n");
    }
}

// Função para salvar os times em um arquivo
void salvarTimes(Time *times, int num_times) {
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

// Função para mostrar a lista de times
void mostrarTimes(Time *times, int num_times) {
    printf("\nLista de Times:\n");
    for (int i = 0; i < num_times; i++) {
        printf("Competicao: %s\n", times[i].nome_campeonato);
        printf("Time: %s\n", times[i].nome_time);
        printf("Numero de jogadores: %d\n\n", times[i].numero_jogadores);
    }
}

// Função principal
int main() {
    printf("BEM VINDO AO PROGRAMA PARA CADASTRAR TIMES NA SUA PROPRIA COMPETICAO. DIVIRTA-SE\n");
    printf("Vamos as Regras:\n");
    printf("1 - Você pode cadastrar no máximo 10 equipes.\n");
    printf("2 - Cada equipe pode ter no mínimo 11 jogadores e no máximo 18.\n");
    printf("3 - Cada equipe pode ter no máximo 3 jogadores estrangeiros.\n");
    printf("4 - Em caso de mais de 3 jogadores estrangeiros, o usuário poderá tentar cadastrar novamente um jogador, desde que este não seja estrangeiro.\n");
    printf("5 - Em caso de times com menos de 11 jogadores ou mais de 18, não será possível sua inscrição na competição e o Programa precisara ser reiniciado.\n");

    Time times[MAX_TIMES];
    int num_times = 0;

    int opcao;
    do {
        cadastrarTime(times, &num_times);
        printf("Deseja cadastrar outro time? (1 para sim, 0 para não): ");
        scanf("%d", &opcao);
    } while (opcao);

    salvarTimes(times, num_times);

    return 0;
}