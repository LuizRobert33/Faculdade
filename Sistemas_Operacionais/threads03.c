#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 200
#define BUFFER_SIZE 2
#define NUM_PROD (NUM_THREADS/2)
#define NUM_CONS (NUM_THREADS/2)

int buffer[BUFFER_SIZE];
int in = 0;  
int out = 0; 

sem_t empty_slots;  
sem_t full_slots;   
pthread_mutex_t mutex;

void print_buffer() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void *producer(void *arg) {
    int id = *(int *)arg;
    free(arg);

    for (int i = 1; i <= BUFFER_SIZE; i++) {
        int item = rand() % 100;

        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("produtor %d: produziu: %d na posicao: %d\n", id, item, in + 1);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);

        print_buffer();
        usleep(100000); 
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int id = *(int *)arg;
    free(arg);

    for (int i = 1; i <= BUFFER_SIZE; i++) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        buffer[out] = 0;
        printf("consumidor %d: consumiu: %d na posicao: %d\n", id, item, out + 1);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);

        print_buffer();
        usleep(100000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producers[NUM_PROD];
    pthread_t consumers[NUM_CONS];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }

 
    for (int i = 0; i < NUM_PROD; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }
   
    for (int i = 0; i < NUM_CONS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

   
    for (int i = 0; i < NUM_PROD; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONS; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
