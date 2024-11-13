#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];

// Philosopher function
void* philosopher(void* num) {
    int i = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking...\n", i);
        //sleep(1);  // Simulate thinking

        // Asymmetry: Philosopher 0 picks up the right fork first
        if (i == 0) {
            sem_wait(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork first
            printf("Philosopher %d picked up right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);
            sem_wait(&forks[i]);  // Then pick up left fork
            printf("Philosopher %d picked up left fork %d\n", i, i);
        } else {
            sem_wait(&forks[i]);  // Pick up left fork first
            printf("Philosopher %d picked up left fork %d\n", i, i);
            sem_wait(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Then pick up right fork
            printf("Philosopher %d picked up right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);
        }

        // Eating
        printf("Philosopher %d is eating...\n", i);
        //sleep(1);  // Simulate eating

        // Put down the forks
        sem_post(&forks[i]);  // Put down left fork
        printf("Philosopher %d put down left fork %d\n", i, i);
        sem_post(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
        printf("Philosopher %d put down right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);

        // Back to thinking
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Each fork is initially available (semaphore value = 1)
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join threads (although in this infinite loop, they will never actually terminate)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL); // waits for a thread to finish executing
    }

    // Destroy semaphores (not reached due to infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}