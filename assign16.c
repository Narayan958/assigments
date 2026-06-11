#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCERS 2
#define CONSUMERS 2
#define ITEMS_PER_PRODUCER 5

int buffer[BUFFER_SIZE];

int in = 0;
int out = 0;


sem_t empty;
sem_t full;


pthread_mutex_t mutex;

void* producer(void* arg)
{
    int id = *(int*)arg;

    for (int i = 1; i <= ITEMS_PER_PRODUCER; i++)
    {
        int item = id * 100 + i;

        // Wait if buffer is full
        sem_wait(&empty);

        // Enter critical section
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d produced item %d at index %d\n",
               id, item, in);

        in = (in + 1) % BUFFER_SIZE;

        // Exit critical section
        pthread_mutex_unlock(&mutex);

        // Signal that buffer has new item
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    int id = *(int*)arg;

    for (int i = 1; i <= ITEMS_PER_PRODUCER; i++)
    {
       
        sem_wait(&full);

        
        pthread_mutex_lock(&mutex);

        int item = buffer[out];

        printf("Consumer %d consumed item %d from index %d\n",
               id, item, out);

        out = (out + 1) % BUFFER_SIZE;

       
        pthread_mutex_unlock(&mutex);

        
        sem_post(&empty);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t prod[PRODUCERS];
    pthread_t cons[CONSUMERS];

    int prod_id[PRODUCERS];
    int cons_id[CONSUMERS];

   
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    
    pthread_mutex_init(&mutex, NULL);

    
    for (int i = 0; i < PRODUCERS; i++)
    {
        prod_id[i] = i + 1;

        pthread_create(&prod[i],
                       NULL,
                       producer,
                       &prod_id[i]);
    }

   
    for (int i = 0; i < CONSUMERS; i++)
    {
        cons_id[i] = i + 1;

        pthread_create(&cons[i],
                       NULL,
                       consumer,
                       &cons_id[i]);
    }

    
    for (int i = 0; i < PRODUCERS; i++)
    {
        pthread_join(prod[i], NULL);
    }

   
    for (int i = 0; i < CONSUMERS; i++)
    {
        pthread_join(cons[i], NULL);
    }

    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll threads finished execution.\n");

    return 0;
}