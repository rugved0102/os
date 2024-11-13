#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILOSOPHERS 5

pthread_mutex_t forks[PHILOSOPHERS]; // Mutexes for forks

void* philosopher(void* num) {
    int id = *((int*)num);
    
    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3); // Philosopher is thinking

        // Pick up both forks
        // To avoid deadlock, always pick up the lower-numbered fork first
        if (id % 2 == 0) { // Even numbered philosophers pick up the left fork first
            pthread_mutex_lock(&forks[id]); // Pick up left fork
            pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]); // Pick up right fork
        } else { // Odd numbered philosophers pick up the right fork first
            pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]); // Pick up right fork
            pthread_mutex_lock(&forks[id]); // Pick up left fork
        }

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 3); // Philosopher is eating

        // Put down both forks
        pthread_mutex_unlock(&forks[(id + 1) % PHILOSOPHERS]); // Put down right fork
        pthread_mutex_unlock(&forks[id]); // Put down left fork
    }
}

int main() {
    pthread_t philosophers[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

    // Initialize mutexes
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL); // Initialize each fork mutex
    }

    // Create philosopher threads
    for (int i = 0; i < PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void*)&ids[i]);
    }

    // Wait for philosopher threads to finish (they won't, in this case)
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up (this code will never be reached)
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]); // Destroy each fork mutex
    }

    return 0;
}