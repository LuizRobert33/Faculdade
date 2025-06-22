// threads02.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAM_VETOR 5
#define PRODUCOES 10

int buffer[TAM_VETOR];
int in = 0, out = 0;
int count = 0; // itens no buffer
int turn = 0;  // 0 = produtor, 1 = consumidor

pthread_mutex_t lock;

void *produtor(void *arg) {
    int i;
    for (i = 0; i < PRODUCOES; i++) {
        while (turn != 0); // espera sua vez

        pthread_mutex_lock(&lock);

        if (count < TAM_VETOR) {
            int valor = rand() % 100;
            buffer[in] = valor;
            in = (in + 1) % TAM_VETOR;
            count++;
            printf("Produtor produziu %d\n", valor);
        }

        turn = 1; // passa a vez ao consumidor
        pthread_mutex_unlock(&lock);
        usleep(100000); // atraso para simular produção
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg) {
    int i;
    for (i = 0; i < PRODUCOES; i++) {
        while (turn != 1); // espera sua vez

        pthread_mutex_lock(&lock);

        if (count > 0) {
            int valor = buffer[out];
            out = (out + 1) % TAM_VETOR;
            count--;
            printf("Consumidor consumiu %d\n", valor);
        }

        turn = 0; // passa a vez ao produtor
        pthread_mutex_unlock(&lock);
        usleep(100000); // atraso para simular consumo
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t_produtor, t_consumidor;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t_produtor, NULL, produtor, NULL);
    pthread_create(&t_consumidor, NULL, consumidor, NULL);

    pthread_join(t_produtor, NULL);
    pthread_join(t_consumidor, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
