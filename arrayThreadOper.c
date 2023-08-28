/* Write a thread program to demonstarate the Average,Maximum and Minumum Elemen Finding */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define NUM_THREADS 3

int size;
int arr[100];
double avg;
int maxi,mini;

void *findAverage(){
    int sum = 0;
    for(int i=0;i<size;i++){
        sum+=arr[i];
    }
    avg = (1.0*sum)/size;
    return NULL;
}

void *findMaximum(){
    maxi = arr[0];
    for(int i=1;i<size;i++){
        if(arr[i]>maxi){
            maxi = arr[i];
        }
    }
    return NULL;
}

void *findMinimum(){
    mini = arr[0];
    for(int i=1;i<size;i++){
        if(arr[i]<mini){
            mini = arr[i];
        }
    }
    return NULL;
}

int main(){
    printf("Enter the size of Array : \n");
    scanf("%d",&size);
    
    printf("Enter the elements of Array : \n");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    
    pthread_t threads[NUM_THREADS];
    
    pthread_create(&threads[0],NULL,findAverage,NULL);
    pthread_create(&threads[1],NULL,findMaximum,NULL);
    pthread_create(&threads[2],NULL,findMinimum,NULL);
    
    for(int i=0;i<NUM_THREADS;i++){
        pthread_join(threads[i],NULL);
    }
    
    printf("Maximum Number : %d\n",maxi);
    printf("Minimum Number : %d\n",mini);
    printf("Average Number : %.2f\n",avg);
    
}
