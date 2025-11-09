#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FILENAME "shared_buffer.txt"

sem_t sem_empty;
sem_t sem_full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    FILE *fp;
    int item;

    for (int i = 0; i < 10; i++)
    {
        item = rand() % 10;

        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);

        fp = fopen(FILENAME, "w");
        fprintf(fp, "%d", item);
        fclose(fp);

        printf("Producer produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);

        usleep((rand() % 101) * 1000);
    }
    return NULL;
}

void *consumer(void *arg)
{
    FILE *fp;
    int item;

    for (int i = 0; i < 10; i++)
    {
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);

        fp = fopen(FILENAME, "r");
        fscanf(fp, "%d", &item);
        fclose(fp);

        printf("Consumer consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t prod_thread, cons_thread;

    sem_init(&sem_empty, 0, 1);
    sem_init(&sem_full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    printf("Producer–Consumer Simulation Started (File-based)\n\n");

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("\nSimulation Finished.\n");

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);

    return 0;
}
