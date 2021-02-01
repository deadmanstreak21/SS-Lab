#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 10
#define MAX_ITEMS 20

int empty=10,full=0;
int buffer[BUFFER_SIZE];


sem_t lock;

void *producer(void *);
void *consumer(void *);

void Wait(int *value){
    while(*value==0);
    *value=*value-1;
}

void Signal(int *value){
    *value=*value+1;
}


void main(){
    pthread_t c_id,p_id;
    
    sem_init(&lock,0,1);

    int a=0,b=1;

    pthread_create(&c_id,NULL,consumer,(void *)&a);
    pthread_create(&p_id,NULL,producer,(void *)&b);

    pthread_join(p_id,NULL);
    pthread_join(c_id,NULL);
}

void *producer(void *id){
    printf("producer started\n");
    int in=0;
    for(int i=0;i<MAX_ITEMS;i++){
        Wait(&empty);
        sem_wait(&lock);
        buffer[in]=rand();
        printf("Producer produced %d\n",buffer[in]);
        in=(in+1)%BUFFER_SIZE;
        sem_post(&lock);
        Signal(&full);
    }
}

void *consumer(void *id){
    printf("consumer started\n");
    int out=0;
    for(int i=0;i<MAX_ITEMS;i++){
        Wait(&full);
        sem_wait(&lock);
        printf("Consumer consumed %d\n",buffer[out]);
        out=(out+1)%BUFFER_SIZE;
        sem_post(&lock);
        Signal(&empty);
    }
}
