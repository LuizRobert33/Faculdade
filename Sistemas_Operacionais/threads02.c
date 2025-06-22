#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define TAM_VETOR 3
#define TOTAL_THREADS 5

int buffer[TAM_VETOR] = {0};
int in = 0, out = 0;
int turn = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void imprimir_vetor() {
    for (int i = 0; i < TAM_VETOR; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void *produtor(void *arg) {
    int id = *(int *)arg;

    while (1) {
        while (turn != 0); 
        pthread_mutex_lock(&mutex);

        for (int i = 0; i < TAM_VETOR; i++) {
            int valor = rand() % 100;
            buffer[in] = valor;
            printf("produtor %d: produziu: %d na posicao: %d\n", id, valor, in + 1);
            in = (in + 1) % TAM_VETOR;
        }
        imprimir_vetor();
        usleep(300000); 

        turn = 1; 
        pthread_mutex_unlock(&mutex);
        break;
    }

    pthread_exit(NULL);
}

void *consumidor(void *arg) {
    int id = *(int *)arg;

    while (1) {
        while (turn != 1); 
        pthread_mutex_lock(&mutex);

        for (int i = 0; i < TAM_VETOR; i++) {
            int valor = buffer[out];
            printf("consumidor %d: consumiu: %d na posicao: %d\n", id, valor, out + 1);
            buffer[out] = 0;
            out = (out + 1) % TAM_VETOR;
        }
        imprimir_vetor();
        usleep(300000); 

        turn = 0; 
        pthread_mutex_unlock(&mutex);
        break;
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t produtores[TOTAL_THREADS];
    pthread_t consumidores[TOTAL_THREADS];
    int ids[TOTAL_THREADS];

    for (int i = 0; i < TOTAL_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&produtores[i], NULL, produtor, &ids[i]);
        pthread_join(produtores[i], NULL);

        pthread_create(&consumidores[i], NULL, consumidor, &ids[i]);
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}
