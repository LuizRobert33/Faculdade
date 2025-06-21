#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILHOS 2

void* func_filho(void* arg) {
    int id = *((int*)arg);
    printf("Alô do filho %d!\n", id);
    sleep(1); // simula trabalho
    printf("Tchau do filho %d!\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_FILHOS];
    int ids[NUM_FILHOS];

    printf("Alô do pai!\n");

    for (int i = 0; i < NUM_FILHOS; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, func_filho, (void*)&ids[i]) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_FILHOS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Tchau do pai!\n");
    return 0;
}
