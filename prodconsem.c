#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 5


sem_t empty, full;
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;


void *producer(void *arg) {
    int producer_id = *((int *)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);


        buffer[in] = i;
        printf("Producer %d: produced item %d\n", producer_id, i);
        in = (in + 1) % BUFFER_SIZE;
        usleep(100000);


        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}


void *consumer(void *arg) {
    int consumer_id = *((int *)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);


        int item = buffer[out];
        printf("Consumer %d: consumed item %d\n", consumer_id, item);
        out = (out + 1) % BUFFER_SIZE;
        usleep(150000);


        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}


int main() {
    int num_producers = 2, num_consumers = 2;
    pthread_t producers[num_producers], consumers[num_consumers];
    int producer_ids[num_producers], consumer_ids[num_consumers];


    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);


    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }


    for (int i = 0; i < num_producers; i++)
        pthread_join(producers[i], NULL);
    for (int i = 0; i < num_consumers; i++)
        pthread_join(consumers[i], NULL);


    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}

