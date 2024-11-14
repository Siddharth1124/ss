#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t w_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg)
{

        pthread_mutex_lock(&r_mutex);
            
            read_count++;
            if (read_count == 1)
                pthread_mutex_lock(&w_mutex);

            printf("Reader %d: read shared data = %d\n ", *(int *)arg, shared_data);

            read_count--;
            if (read_count == 0)
                pthread_mutex_unlock(&w_mutex);
                
        pthread_mutex_unlock(&r_mutex);
 
    return NULL;
}

void *writer(void *arg)
{
        pthread_mutex_lock(&w_mutex);
            shared_data++;
            printf("Writer %d: wrote shared data = %d\n", *(int *)arg, shared_data);
        pthread_mutex_unlock(&w_mutex);
   
    return NULL;
}

int main()
{
    int nr, nw;
    
    printf("Number of Readers : ");
    scanf("%d", &nr);
    printf("Number of Writers : ");
    scanf("%d", &nw);
    printf("\n\n");

    pthread_t r[nr], w[nw];

    for(int i = 0; i < nw; i++)
	  pthread_create(&w[i], NULL, writer, &i);
		
    printf("\n");
	
    for(int i = 0; i < nr; i++)
		pthread_create(&r[i], NULL, reader, &i);
	
    for(int i = 0; i < nr; i++)
	  pthread_join(r[i], NULL);
		
	for(int i = 0; i < nw; i++)
	  pthread_join(w[i], NULL);
   
    return 0;
}