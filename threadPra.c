#include<stdio.h>
#include<pthread.h>

char *a;

void *threadFunction(){
	printf("In thread Function\n");
	pthread_exit("Exit Thread Function\n");
}

int main(){
	//void *a;
	pthread_t thread1;
	pthread_create(&thread1,NULL,threadFunction,NULL);
	pthread_join(thread1,&a);
	printf("%s \n",a);

	return 0;
}


