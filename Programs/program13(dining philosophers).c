#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<windows.h>

// semaphores
sem_t chopsticks[50];
sem_t room;

// function definition
void * philosophers(void *);
void eat(int);

int n;
void main(){
    int i,a[50];
    pthread_t thread_id[50];

    printf("Enter the number of philosophers:");
    scanf("%d",&n);

    // initializing semaphores
    sem_init(&room,0,n-1);
    for(i=0;i<n;i++){
        sem_init(&chopsticks[i],0,1);
    }

    // creating threads
    for(i=0;i<n;i++){
        a[i]=i;
        pthread_create(&thread_id[i],NULL,philosophers,(void *)&a[i]);
    }

    // waiting for thread termination
    for(i=0;i<n;i++){
        pthread_join(thread_id[i],NULL);
    }
}

void * philosophers(void * num){
    int phil=*(int *)num;

    sem_wait(&room);

    sem_wait(&chopsticks[phil]);
    sem_wait(&chopsticks[(phil+1)%n]);

    eat(phil);
    Sleep(2);
    
    printf("Philosopher %d has finished eating\n",phil+1);

    sem_post(&chopsticks[(phil+1)%n]);
    sem_post(&chopsticks[phil]);

    sem_post(&room);
}

void eat(int phil){
    printf("Philosopher %d is eating\n",phil+1);
}
