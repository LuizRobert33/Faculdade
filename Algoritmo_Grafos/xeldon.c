#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

enum OpcaoJogo { OPCAO_PEDRA = 1, OPCAO_PAPEL, OPCAO_TESOURA, OPCAO_LAGARTO, OPCAO_SPOCK };

char lerTeclaComTimeout() {
    struct termios configAntiga, configNova;
    char tecla;
    tcgetattr(STDIN_FILENO, &configAntiga);
    configNova = configAntiga;
    configNova.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &configNova);

    fd_set conjunto;
    struct timeval tempoEspera;

    FD_ZERO(&conjunto);
    FD_SET(STDIN_FILENO, &conjunto);

    tempoEspera.tv_sec = 5;
    tempoEspera.tv_usec = 0;

    int resultado = select(1, &conjunto, NULL, NULL, &tempoEspera);

    if(resultado == 1) {
        tecla = getchar();
    } else {
        tecla = -1;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &configAntiga);
    return tecla;
}

int converterTeclaJogador1(char tecla) {
    if(tecla != -1){
        switch (tecla) {
            case 'Q': case 'q': return OPCAO_PEDRA;
            case 'W': case 'w': return OPCAO_PAPEL;
            case 'A': case 'a': return OPCAO_TESOURA;
            case 'S': case 's': return OPCAO_LAGARTO;
            case 'D': case 'd': return OPCAO_SPOCK;
            default: return -2;
        }
    }
    return -1;
}

int converterTeclaJogador2(char tecla) {
    if(tecla != -1) {
        switch (tecla) {
            case 'U': case 'u': return OPCAO_PEDRA;
            case 'I': case 'i': return OPCAO_PAPEL;
            case 'J': case 'j': return OPCAO_TESOURA;
            case 'K': case 'k': return OPCAO_LAGARTO;
            case 'L': case 'l': return OPCAO_SPOCK;
            default: return -2;
        }
    }
    return -1;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMensagemRodada(int escolha1, int escolha2, int rodada, int vencedor, int pontos1, int pontos2) {
    printf("RODADA %d:\n", rodada+1);
    switch(escolha1){
        case 1: printf("PEDRA x "); break;
        case 2: printf("PAPEL x "); break;
        case 3: printf("TESOURA x "); break;
        case 4: printf("LAGARTO x "); break;
        case 5: printf("SPOCK x "); break;
    }
    switch(escolha2){
        case 1: printf("PEDRA\n"); break;
        case 2: printf("PAPEL\n"); break;
        case 3: printf("TESOURA\n"); break;
        case 4: printf("LAGARTO\n"); break;
        case 5: printf("SPOCK\n"); break;
    }

    switch (vencedor) {
    case 1:
        if(pontos1 == 1)
            printf("Jogador 1: %d ponto (+1)\n", pontos1); 
        else
            printf("Jogador 1: %d pontos (+1)\n", pontos1); 
        if(pontos2 == 1)
            printf("Jogador 2: %d ponto\n", pontos2); 
        else
            printf("Jogador 2: %d pontos\n", pontos2); 
        break;
    case 2: 
        if(pontos1 == 1)
            printf("Jogador 1: %d ponto\n", pontos1); 
        else
            printf("Jogador 1: %d pontos\n", pontos1); 
        if(pontos2 == 1)
            printf("Jogador 2: %d ponto (+1)\n", pontos2); 
        else
            printf("Jogador 2: %d pontos (+1)\n", pontos2); 
        break;
    case 0: printf("Empate!\n"); break;
    }

    printf("\n");
}

void verificarVencedor(int jogada1, int jogada2, int* pontos1, int* pontos2, int* empates, int rodada) {
    int vencedor;
    if (jogada1 == jogada2) {
        (*empates)++;
        vencedor = 0;
        exibirMensagemRodada(jogada1, jogada2, rodada, vencedor, *pontos1, *pontos2);
    } else if ((jogada1 == OPCAO_TESOURA && (jogada2 == OPCAO_PAPEL || jogada2 == OPCAO_LAGARTO)) ||
        (jogada1 == OPCAO_PAPEL && (jogada2 == OPCAO_PEDRA || jogada2 == OPCAO_SPOCK)) ||
        (jogada1 == OPCAO_PEDRA && (jogada2 == OPCAO_TESOURA || jogada2 == OPCAO_LAGARTO)) ||
        (jogada1 == OPCAO_LAGARTO && (jogada2 == OPCAO_SPOCK || jogada2 == OPCAO_PAPEL)) ||
        (jogada1 == OPCAO_SPOCK && (jogada2 == OPCAO_TESOURA || jogada2 == OPCAO_PEDRA))) {
        (*pontos1)++;
        vencedor = 1;
        exibirMensagemRodada(jogada1, jogada2, rodada, vencedor, *pontos1, *pontos2);
    } else {
        (*pontos2)++; 
        vencedor = 2;
        exibirMensagemRodada(jogada1, jogada2, rodada, vencedor, *pontos1, *pontos2);
    }
}

int gerarJogadaComputador() {
    return (rand() % 5) + 1;
}

void exibirMenuAdversario() {
    printf("Escolha o modo de jogo:\n");
    printf("1. VS Player\n");
    printf("2. VS Maquina\n");
}

void exibirOpcoesJogador1() {
    printf("Faça sua escolha, jogador 1:\n");
    printf("Q. Pedra\n");
    printf("W. Papel\n");
    printf("A. Tesoura\n");
    printf("S. Lagarto\n");
    printf("D. Spock\n");
}

void exibirOpcoesJogador2() {
    printf("Faça sua escolha, jogador 2:\n");
    printf("U. Pedra\n");
    printf("I. Papel\n");
    printf("J. Tesoura\n");
    printf("K. Lagarto\n");
    printf("L. Spock\n");
}

void exibirMensagemFinal(int pontos1, int pontos2, int empates) {
    printf("FIM DA PARTIDA!\n");
    if (pontos1 > pontos2) {
        if (pontos1 == 1)
            printf("JOGADOR 1: YOU WIN! (%d ponto)\n", pontos1);
        else   
            printf("JOGADOR 1: YOU WIN! (%d pontos)\n", pontos1);
        if (pontos2 == 1)
            printf("JOGADOR 2: YOU LOSE! (%d ponto)\n", pontos2);
        else
            printf("JOGADOR 2: YOU LOSE! (%d pontos)\n", pontos2);
    } else if (pontos2 > pontos1) {
        if (pontos2 == 1)
            printf("JOGADOR 2: YOU WIN! (%d ponto)\n", pontos2);
        else
            printf("JOGADOR 2: YOU WIN! (%d pontos)\n", pontos2);
        if (pontos1 == 1)
            printf("JOGADOR 1: YOU LOSE! (%d ponto)\n", pontos1);
        else   
            printf("JOGADOR 1: YOU LOSE! (%d pontos)\n", pontos1);
    } else {
        if(pontos1 >= 1 && pontos2 >= 1)
            if(pontos1 == 1 || pontos2 == 1)
                printf("EMPATE!  (%d ponto pra cada)\n", pontos1);
            else
                printf("EMPATE!  (%d pontos pra cada)\n", pontos1);
        else {
            printf("EMPATE!\n");
        }
    }
    if(empates == 1)
        printf("%d Ponto de Empate\n", empates);
    else
        printf("%d Pontos de Empate\n", empates);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void escolherTempoPartida(int *tempoPartida){
    int opcaoTempo=0;
    printf("Qual o tempo de jogo?\n");
    printf("1. 30s\n");
    printf("2. 45s\n");
    printf("3. 60s\n");
    while (1) {
        if (scanf("%d", &opcaoTempo) != 1) {
            printf("Escolha uma opção válida (1, 2 ou 3).\n");
            limparBufferEntrada();
        } else if (opcaoTempo >= 1 && opcaoTempo <= 3) {
            switch (opcaoTempo) {
                case 1: *tempoPartida = 30; break;
                case 2: *tempoPartida = 45; break;
                case 3: *tempoPartida = 60; break;
            }
            break;
        } else {
            printf("Escolha uma opção válida (1, 2 ou 3).\n");
        }
    }
}

void pontuarPenalidade(int jogada1, int jogada2, int* pontos1, int* pontos2){
    if (jogada1 == -1 && jogada2 == -1) {
        printf("Os dois não digitaram uma tecla. Nenhum ganha ponto.\n");
    } else if (jogada1 == -2 && jogada2 == -2) {
        printf("Os dois apertaram teclas erradas. Nenhum ganha ponto.\n");
    } else if (jogada1 < 0 && jogada2 < 0){
        printf("Os dois cometeram penalidades. Nenhum ganha ponto.\n");
    }
    else {
        if (jogada1 == -1) {
            printf("ERRO: Jogador 1 não digitou uma tecla. +1 para o adversário\n");
            (*pontos2)++;
        } else if (jogada1 == -2) {
            printf("ERRO: Jogador 1 apertou a tecla errada. +1 para o adversário\n");
            (*pontos2)++;
        }
        if (jogada2 == -1) {
            printf("ERRO: Jogador 2 não digitou uma tecla. +1 para o adversário\n");
            (*pontos1)++;
        } else if (jogada2 == -2) {
            printf("ERRO: Jogador 2 apertou a tecla errada. +1 para o adversário\n");
            (*pontos1)++;
        }
    }
}

int main() {
    int jogada1, jogada2, modoAdversario, resultado, rodadaAtual = 0, tempoPartida = 0;
    char teclaJ1, teclaJ2;
    int pontosJogador1 = 0, pontosJogador2 = 0, totalEmpates = 0;
    time_t tempoInicio, tempoFim;

    srand(time(NULL));
    limparTela();
    exibirMenuAdversario();
    scanf("%d", &modoAdversario);
    limparTela();
    escolherTempoPartida(&tempoPartida);
    limparTela();

    limparBufferEntrada();
    if (modoAdversario == 1) {
        time(&tempoInicio);
        tempoFim = tempoInicio; // CORREÇÃO

        while (difftime(tempoFim, tempoInicio) < tempoPartida) {
            printf("-----------------------------------------------------\n");
            printf("Rodada %d\n", rodadaAtual + 1);

            exibirOpcoesJogador1();
            teclaJ1 = lerTeclaComTimeout();
            printf("\n ");

            exibirOpcoesJogador2();
            teclaJ2 = lerTeclaComTimeout();
            printf("\n");

            jogada1 = converterTeclaJogador1(teclaJ1);
            jogada2 = converterTeclaJogador2(teclaJ2);

            if(jogada1 > 0 && jogada2 > 0){
                verificarVencedor(jogada1, jogada2, &pontosJogador1, &pontosJogador2, &totalEmpates, rodadaAtual);
            }else{
                pontuarPenalidade(jogada1, jogada2, &pontosJogador1, &pontosJogador2);
            }
            
            time(&tempoFim);
            rodadaAtual++;
        }
    } else if (modoAdversario == 2) {
        time(&tempoInicio);
        tempoFim = tempoInicio; // CORREÇÃO

        while (difftime(tempoFim, tempoInicio) < tempoPartida) {
            printf("-----------------------------------------------------\n");
            printf("Rodada %d\n", rodadaAtual + 1);

            exibirOpcoesJogador1();
            teclaJ1 = lerTeclaComTimeout();
            jogada1 = converterTeclaJogador1(teclaJ1);
            printf("\n");

            jogada2 = gerarJogadaComputador();
            
            if(jogada1 > 0 && jogada2 > 0){
                verificarVencedor(jogada1, jogada2, &pontosJogador1, &pontosJogador2, &totalEmpates, rodadaAtual);
            }else{
                pontuarPenalidade(jogada1, jogada2, &pontosJogador1, &pontosJogador2);
            }

            time(&tempoFim);
            rodadaAtual++;
        }

    } else {
        printf("Escolha uma opção válida!\n");
    }

    if(rodadaAtual > 0){
        exibirMensagemFinal(pontosJogador1, pontosJogador2, totalEmpates);
        printf("%d Rodadas Jogadas\n", rodadaAtual);

    }
}