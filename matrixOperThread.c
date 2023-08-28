#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define THREADS_NUM 3
int size;
int mat1[100][100],mat2[100][100];
int add[100][100],sub[100][100],mul[100][100];

void *addition(){
    for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
             add[i][j] = mat1[i][j] + mat2[i][j];
         }
    }
    
    printf("Addition of two matrices : \n");
    for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
            printf("%d ",add[i][j]);
         }
        printf("\n");
    }
}

void *substraction(){
    for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
             sub[i][j] = mat1[i][j] - mat2[i][j];
         }
    }
    
    printf("Substraction of two matrices : \n");
    for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
            printf("%d ",sub[i][j]);
         }
        printf("\n");
    }
}

void *multiplication(){
    
    for(int i=0;i<size;i++){
     for(int j=0;j<size;j++){
         int sum = 0;
         for(int k=0;k<size;k++){
             sum+=(mat1[k][j]*mat2[i][k]);
         }
         mul[i][j]=sum;
        }
    }
    
    printf("Multiplication of two matrices : \n");
    for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
            printf("%d ",mul[i][j]);
         }
        printf("\n");
    }
    
}

int main(){
    
    printf("Enter the size of Array : \n");
    scanf("%d",&size);
    
    printf("Enter the elements of Array 1 : \n");
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            scanf("%d",&mat1[i][j]);
        }
    }
    
    printf("Enter the elements of Array 2 : \n");
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            scanf("%d",&mat2[i][j]);
        }
    }
    
    pthread_t threads[THREADS_NUM];
    
    pthread_create(&threads[0],NULL,addition,NULL);
    pthread_create(&threads[1],NULL,substraction,NULL);
    pthread_create(&threads[2],NULL,multiplication,NULL);
    
    for(int i=0;i<size;i++){
        pthread_join(threads[i],NULL);
    }
    
    
    return 0;
}

