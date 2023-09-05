// Producer-Consumer : Thread & Mutex
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define maxBuffer 10
char* bufferQueue;
int bufferIndex=0;

pthread_mutex_t mutexVar=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qEmpty=PTHREAD_COND_INITIALIZER;
pthread_cond_t qFull=PTHREAD_COND_INITIALIZER;


void *producer(){
    while(1){
        pthread_mutex_lock(&mutexVar);
        if(bufferIndex == maxBuffer){
            pthread_cond_wait(&qEmpty,&mutexVar);
        }
        bufferQueue[bufferIndex++]='@';
        printf("Producer : %d\n",bufferIndex);
        pthread_mutex_unlock(&mutexVar);
        pthread_cond_signal(&qFull);
    }
}

void *consumer(){
    while(1){
        pthread_mutex_lock(&mutexVar);
        if(bufferIndex==-1){
            pthread_cond_wait(&qFull,&mutexVar);
        }
        printf("Consumer : %d\n",bufferIndex--);
        pthread_mutex_unlock(&mutexVar);
        pthread_cond_signal(&qEmpty);
    }

}


int main(){
    pthread_t producerThread,consumerThread;
    bufferQueue=(char *)malloc(sizeof(char)*maxBuffer);
    pthread_create(&producerThread,NULL,producer,NULL);
    pthread_create(&consumerThread,NULL,consumer,NULL);

    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);

    return 0;
}

