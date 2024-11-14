#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int np,nc;

void *producer(void *param)
{
    int item = rand() % 100;
    sleep(1);
    sem_wait(&empty);
        
    pthread_mutex_lock(&mutex);
	    buffer[count] = item;
	    count++;
	    printf("Produced item: %d\n", item);
    pthread_mutex_unlock(&mutex);
        
    sem_post(&full); 
    pthread_exit(0);
}

void *consumer(void *param)
{
    sem_wait(&full);
		
    pthread_mutex_lock(&mutex);
		sleep(1);
	    count--;
	    int item = buffer[count];
	    printf("Consumed item: %d\n", item);
    pthread_mutex_unlock(&mutex);
        
    sem_post(&empty);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    printf("Number of Producers : ");
    scanf("%d", &np);
    printf("Number of Consumers : ");
    scanf("%d", &nc);
    printf("\n\n");

    pthread_t p[np], c[nc];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for(int i = 0; i < np; i++)
		pthread_create(&p[i], NULL, producer, NULL);
		
	sleep(1.15*np);
    printf("\n");
	
	for(int i = 0; i < nc; i++)
	  pthread_create(&c[i], NULL, consumer, NULL);

    for(int i = 0; i < np; i++)
	  pthread_join(p[i], NULL);
		
	for(int i = 0; i < nc; i++)
	  pthread_join(c[i], NULL);
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}