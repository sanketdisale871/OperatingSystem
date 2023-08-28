#include<stdio.h>
#include<pthread.h>

void *findFactorial(void *arg){
	int *num = (int *)arg;
	int fact = 1;

	for(int i=1;i<=*num;i++){
		fact*=i;
	}	
	printf("Factorial :%d\n ",fact);
	return NULL;
}

void *checkEvenOdd(void *args){
	int *num = (int *)args;

	if((*num)&1){
	printf("%d is Odd Number.",*num);	}
	else {
	 printf("%d is Even  Number.",*num);		
	}
	return NULL;
}

int main(){

	int num;
	scanf("%d",&num);

	pthread_t th1,th2;
	pthread_create(&th1,NULL,findFactorial,(void *)&num);
	pthread_create(&th2,NULL,checkEvenOdd,(void *)&num);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
}
