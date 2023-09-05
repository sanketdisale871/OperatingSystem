#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define PHILOSOPHERS 5

pthread_mutex_t forks[PHILOSOPHERS];
sem_t semaphore;

void *philosophers(void *args){
    int id = *(int *)args;
    free(args);

    int leftFork = id;
    int rightFork = (id+1)%PHILOSOPHERS;

    while(1){
        printf("Philosopher %d is Thinking.",id);
        sleep(1);
        printf("Philosopher %d is Hungry.\n",id);

        sem_wait(&semaphore);

        pthread_mutex_lock(&forks[leftFork]);
        printf("Philosopher %d picked up fork %d (left).\n",id,leftFork);
        sleep(1);

        pthread_mutex_lock(&forks[rightFork]);
        printf("Philosopher %d picked up fork %d (right)\n",id,rightFork);

        printf("Philosopher %d is Eating.\n",id);
        sleep(2);

        pthread_mutex_unlock(&forks[leftFork]);
        printf("Philosopher %d put down fork %d (left).\n",id,leftFork);

        pthread_mutex_unlock(&forks[rightFork]);
        printf("Philosopher %d put down the fork %d (right).\n",id,rightFork);

        sem_post(&semaphore);
    }
}

int main(){
    sem_init(&semaphore,0,PHILOSOPHERS);

    // Intialize the forks (mutexes)
    for(int i=0;i<PHILOSOPHERS;i++){
        pthread_mutex_init(&forks[i],NULL);
    }

    pthread_t philoThread[PHILOSOPHERS];

    for(int i=0;i<PHILOSOPHERS;i++){
        int *philoId = (int *)malloc(sizeof(int));
        *philoId=i+1;
        pthread_create(&philoThread[i],NULL,philosophers,philoId);
    }

    // Wait for philosophers thread to finish 
    for(int i=0;i<PHILOSOPHERS;i++){
        pthread_join(philoThread[i],NULL);
    }

    // Cleaning Work
    for(int i=0;i<PHILOSOPHERS;i++){
        pthread_mutex_destroy(&forks[i]);
    }

    sem_destroy(&semaphore);


    return 0;
}