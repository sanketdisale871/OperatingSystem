#include<stdio.h>
#include<pthread.h>

void *threadFunction(void* argu){
	int *p = (int *) argu;
	printf("Argument : %d",*p);
	return "ArgumentPrinted";
}

int main(){
	void *status;
	int funArgs = 10;

	pthread_t thread1;
	pthread_create(&thread1,NULL,threadFunction,(void *)&funArgs);
	pthread_join(thread1,&status);
	printf("%s \n",(char *) status);
	return 0;
}
