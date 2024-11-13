#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5 // Number of reader threads
#define WRITERS 2 // Number of writer threads

// Shared resource
int shared_resource = 0;

// Semaphores
sem_t mutex;   // For mutual exclusion
sem_t wrt;     // Writer semaphore
int read_count = 0; // Number of active readers

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);
    
    while (1) {
        // Wait for mutex to update read_count
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt); // If this is the first reader, wait for the writer
        }
        sem_post(&mutex); // Release mutex

        // Critical Section - Reading the shared resource
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);
        sleep(1); // Simulate reading time

        // Wait for mutex to update read_count
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // If this is the last reader, signal the writer
        }
        sem_post(&mutex); // Release mutex

        sleep(rand() % 3); // Simulate thinking time
    }
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        sem_wait(&wrt); // Wait for writer access

        // Critical Section - Writing to the shared resource
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);
        sleep(5); // Simulate writing time

        sem_post(&wrt); // Release writer access

        sleep(rand() % 3); // Simulate thinking time
    }
    return NULL;
}

int main() {
    pthread_t readers[READERS], writers[WRITERS];
    int reader_ids[READERS], writer_ids[WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Binary semaphore for mutual exclusion
    sem_init(&wrt, 0, 1);   // Binary semaphore for writers

    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1; // Assigning IDs to readers
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1; // Assigning IDs to writers
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Wait for threads to finish (they won't in this case)
    for (int i = 0; i < READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}