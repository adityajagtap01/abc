#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];

int in = 0;
int out = 0;

pthread_mutex_t mutex;
sem_t full;
sem_t empty;

void *producer(void *arg)
{
    int item;
    int NUM_ITEMS = 20;

    for (int i = 0; i < NUM_ITEMS; i++)
    {

        item = rand() % 100;
        sleep(rand() % 3);

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producers produced %d from index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int item;
    int NUM_ITEMS = 20;

    for (int i = 0; i < NUM_ITEMS; i++)
    {

        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);

        sleep(rand() % 3);
    }
    return NULL;
}

int main()
{

    pthread_t prod_thread, cons_thread;

    printf("Producer-Consumer Simulation Started::\n");
    printf("Buffer Size :%d\n", BUFFER_SIZE);

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("Simulation Finished.\n");
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}