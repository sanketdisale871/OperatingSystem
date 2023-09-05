#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>


/* Intialization */
#define READERS 5
# define WRITERS 2

sem_t wrt; // Binary Semaphore used to both for mutual exclusion and singalling
pthread_mutex_t mutexVari;
int readCnt=0;

int cnt = 2; // Shared Variable


/* Writer Function : */
void *writer(void *args){
    int writerId = *(int *)args;
    free(args);

    while(1){
        sem_wait(&wrt);
        cnt = (cnt*2)%1000;
        printf("Writer : %d\tCount Changed : %d\n",writerId,cnt);
        sem_post(&wrt);
        sleep(1);
    }
}

/* Reader Function */
void *reader(void *args){
    int readerId= *(int *)args;
    free(args);

    while(1){
    pthread_mutex_lock(&mutexVari);
    readCnt++;
    if(readCnt==1){
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutexVari);

    printf("Reader : %d\t reads count : %d\n",readerId,cnt);

    pthread_mutex_lock(&mutexVari);
    readCnt--;
    if(readCnt==0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutexVari);
    sleep(1);
    }
}

int main(){
    sem_init(&wrt,0,1);
    pthread_mutex_init(&mutexVari,NULL);

    pthread_t readerThreads[READERS];
    pthread_t writerThreads[WRITERS];

    for(int i=0;i<WRITERS;i++){
        int *writerId=(int *)malloc(sizeof(int));
        *writerId=i+1;
        pthread_create(&writerThreads[i],NULL,writer,writerId);
    }

    for(int i=0;i<READERS;i++){
        int *readId=(int *)malloc(sizeof(int));
        *readId=i+1;
        pthread_create(&readerThreads[i],NULL,reader,readId);
    }

    for(int i=0;i<WRITERS;i++){
        pthread_join(writerThreads[i],NULL);
    }

    for(int i=0;i<READERS;i++){
        pthread_join(readerThreads[i],NULL);
    }
    
    pthread_mutex_destroy(&mutexVari);
    sem_destroy(&wrt);

    return 0;
}