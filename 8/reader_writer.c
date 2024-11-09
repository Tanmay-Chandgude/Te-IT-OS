// Reader-Writer Problem Solution using Semaphores
#include <stdio.h>        // Standard Input/Output library
#include <semaphore.h>    // Semaphore library for synchronization
#include <pthread.h>      // Library for threading
#include <stdlib.h>       // Standard library for general functions
#include <unistd.h>       // Provides sleep function for delays

// Define two semaphores: `mutex` for mutual exclusion among readers and `wrt` for writers
sem_t mutex, wrt;
int data = 0, rcnt = 0;  // `data` holds the shared data; `rcnt` keeps count of active readers

// Reader function to read the shared data
void* reader(void *arg) {
    // Entry section for reader
    sem_wait(&mutex);           // Lock mutex to update the reader count
    rcnt = rcnt + 1;            // Increment the reader count
    if (rcnt == 1)              // If this is the first reader,
        sem_wait(&wrt);         // block writers by locking wrt semaphore
    sem_post(&mutex);           // Release mutex after updating reader count

    // Critical section for reader
    printf("data is read %d\n", data);  // Reading the shared data
    sleep(1);                          // Simulating reading delay

    // Exit section for reader
    sem_wait(&mutex);           // Lock mutex to update reader count
    rcnt = rcnt - 1;            // Decrement the reader count
    if (rcnt == 0)              // If this is the last reader,
        sem_post(&wrt);         // allow writers by unlocking wrt semaphore
    sem_post(&mutex);           // Release mutex after updating reader count
}

// Writer function to write to the shared data
void* writer(void *arg) {
    sem_wait(&wrt);             // Lock wrt semaphore to block all readers and writers

    // Critical section for writer
    data++;                      // Modify the shared data
    printf("data is written %d\n", data);  // Print the updated data
    sleep(1);                    // Simulating writing delay

    sem_post(&wrt);              // Release wrt semaphore to allow other writers or readers
}

int main() {
    int i;
    pthread_t rtid[5], wrtid[5];  // Thread IDs for readers and writers
    sem_init(&mutex, 0, 1);       // Initialize mutex semaphore with a value of 1
    sem_init(&wrt, 0, 1);         // Initialize wrt semaphore with a value of 1

    // Create reader and writer threads
    for (i = 0; i < 2; i++) {
        pthread_create(&wrtid[i], NULL, (void*) writer, NULL);  // Create writer thread
        pthread_create(&rtid[i], NULL, (void*) reader, NULL);   // Create reader thread
    }

    // Wait for all reader and writer threads to complete
    for (i = 0; i < 2; i++) {
        pthread_join(wrtid[i], NULL);  // Wait for writer thread to finish
        pthread_join(rtid[i], NULL);   // Wait for reader thread to finish
    }

    // Clean up and exit
    sem_destroy(&mutex);               // Destroy mutex semaphore
    sem_destroy(&wrt);                 // Destroy wrt semaphore
    return 0;
}
