#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

int shared_flight_data = 100;
int readcount = 0;
// tools
pthread_mutex_t mutex;
sem_t database_lock;

void *reader(void *arg)
{
    long id = (long)arg;
    sleep(rand() % 3);

    printf("Reader %ld is trying to read\n", id);
    // mutex lock
    pthread_mutex_lock(&mutex);
    readcount++;

    if (readcount == 1)
    {
        printf("First reader is enterd %ld,Locking database", id);
        sem_wait(&database_lock);
    }

    pthread_mutex_unlock(&mutex);

    printf("Others Readers %ld reading data\n", id, shared_flight_data);
    sleep(1);
    printf("Reader %ld has Finished its Reading", id);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
    {
        printf("This is the last Reader to Read %ld\n", id);
        sem_post(&database_lock);
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg)
{

    long id = (long)arg;
    sleep(rand() % 3);

    printf("writer %ld is waiting to write\n", id);
    sem_wait(&database_lock);

    printf("Writer %ld is writing data to database..\n", id);
    shared_flight_data += 10;
    sleep(2);
    printf("Writer %ld has finished..!", id, shared_flight_data);

    sem_post(&database_lock);

    return NULL;
}
int main()

{
    pthread_t readers_thread[5];
    pthread_t writers_thread[2];

    printf("Readers Writers Simulation(Reader priority)...\n");

    pthread_mutex_init(&mutex, NULL);

    sem_init(&database_lock, 0, 1);

    printf("Creating readers Thread\n", 5);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&readers_thread[i], NULL, reader, (void *)i);
    }

    printf("Creating writers Thread\n", 2);
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers_thread[i], NULL, writer, (void *)i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers_thread[i], NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers_thread[i], NULL);
    }

    printf("Simulation Finshed..!\n");
    pthread_mutex_destroy(&mutex);
    sem_destroy(&database_lock);

    return 0;
}
