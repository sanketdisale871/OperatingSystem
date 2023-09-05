#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;  // Semaphore to track empty slots in the buffer
sem_t full;   // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex;  // Mutex to protect buffer access

void produce(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

int consume() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

void* producer(void* arg) {
    int producer_id = *(int*)arg;
    free(arg);

    while (1) {
        int item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Enter critical section
        produce(item);
        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);  // Signal that a slot is filled
        printf("Producer %d produced: %d\n", producer_id, item);
        usleep(100000);  // Sleep for a short time
    }
}

void* consumer(void* arg) {
    int consumer_id = *(int*)arg;
    free(arg);

    while (1) {
        sem_wait(&full);  // Wait for a filled slot
        pthread_mutex_lock(&mutex);  // Enter critical section
        int item = consume();
        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty);  // Signal that a slot is empty
        printf("Consumer %d consumed: %d\n", consumer_id, item);
        usleep(150000);  // Sleep for a slightly longer time
    }
}

int main() {
    srand(time(NULL));
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* producer_id = (int*)malloc(sizeof(int));
        *producer_id = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, producer_id);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int* consumer_id = (int*)malloc(sizeof(int));
        *consumer_id = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, consumer_id);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
