#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

# define READERS 3
# define WRITERS 2

int readCnt=0;
int cnt = 2;

pthread_cond_t wrt=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexVari=PTHREAD_MUTEX_INITIALIZER;

void writer(){
    while(1){
        usleep(rand() % 1000000);
        pthread_cond_wait(&wrt,&mutexVari);
        cnt = (cnt*2)%1000;
        printf("Writer : %d\t modifed count : %d\n",cnt,cnt);
        pthread_mutex_unlock(&mutexVari);
        pthread_cond_signal(&wrt);

        // sleep(1);
    }
}

void reader(){
    while(1){
        pthread_mutex_lock(&mutexVari);
        readCnt++;
        if(readCnt==1){
            pthread_cond_wait(&wrt,&mutexVari);
        }
        pthread_mutex_unlock(&mutexVari);

        printf("Reader : %d\t reads count : %d\n",cnt,cnt);

        pthread_mutex_lock(&mutexVari);
        readCnt--;
        if(readCnt==0){
            pthread_cond_signal(&wrt);
        }
        pthread_mutex_unlock(&mutexVari);

        sleep(1);
    }
}

int main(){
   pthread_t readerThreads[READERS];
    pthread_t writerThreads[WRITERS];

    for(int i=0;i<WRITERS;i++){
        int *writerId=(int *)malloc(sizeof(int));
        *writerId=i+1;
        pthread_create(&writerThreads[i],NULL,writer,NULL);
    }

    for(int i=0;i<READERS;i++){
        int *readId=(int *)malloc(sizeof(int));
        *readId=i+1;
        pthread_create(&readerThreads[i],NULL,reader,NULL);
    }

    for(int i=0;i<WRITERS;i++){
        pthread_join(writerThreads[i],NULL);
    }

    for(int i=0;i<READERS;i++){
        pthread_join(readerThreads[i],NULL);
    }
    
    pthread_mutex_destroy(&mutexVari);
    pthread_cond_destroy(&wrt);
    // sem_destroy(&wrt);

    return 0;
}
