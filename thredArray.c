#include<stdio.h>
#include<pthread.h>

void *functionThread(void *arg){
    int *p = (int *)arg;
    
    printf("Values at zero position : %d\n",p[0]);
    return NULL;
}

int main(){
    
    int arr[] = {10,20,30,40,50};
    
    pthread_t th1;
    pthread_create(&th1,NULL,functionThread,(void *)&arr);
    pthread_join(th1,NULL);
    
    return 0;
}
