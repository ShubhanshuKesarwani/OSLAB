#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define items 3
#define size 3

sem_t empty;
sem_t full;
int in=0;
int out=0;
int buff[size];
pthread_mutex_t m;

void* producer(void *arg){
	int *p=(int *)arg;
	for(int i=0;i<items;i++){
		int item= rand();
		sem_wait(&empty);
		pthread_mutex_lock(&m);
		buff[in]=item;
		printf("producer %d insert %d item at index %d\n",*p,buff[in],in);
		in=(in+1)%size;
		pthread_mutex_unlock(&m);
		sem_post(&full);
	}
}
void* consumer(void *arg){
        int *c=(int *)arg;
        for(int i=0;i<items;i++){
                sem_wait(&full);
		int item=buff[out];
                pthread_mutex_lock(&m);
                printf("consumer %d remove %d item from index %d\n",*c,item,out);
                out=(out+1)%size;
                pthread_mutex_unlock(&m);
                sem_post(&empty);
        }
}


int main(){
	pthread_t prod[5],cons[5];
	pthread_mutex_init(&m,NULL);
	sem_init(&empty,0,size);
	sem_init(&full,0,0);

	int arr[3]={1,2,3};
	for(int i=0;i<3;i++){
		pthread_create(&prod[i],NULL,(void *)producer,(void *)&arr[i]);
	}
	for(int i=0;i<3;i++){
                pthread_create(&cons[i],NULL,(void *)consumer,(void *)&arr[i]);
        }
	for(int i=0;i<3;i++){
                pthread_join(prod[i],NULL);
        }

	for(int i=0;i<3;i++){
                pthread_join(cons[i],NULL);

        }
	pthread_mutex_destroy(&m);
	sem_destroy(&empty);
	sem_destroy(&full);
}
