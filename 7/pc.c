#include <pthread.h>  // Library for creating and managing threads
#include <semaphore.h> // Library for semaphore functions
#include <stdlib.h>    // Standard library for functions like rand()
#include <stdio.h>     // Standard I/O library for printf()

/*
This program provides a possible solution for the producer-consumer problem using mutexes and semaphores.
In this example, there are 5 producers and 5 consumers demonstrating concurrent access to a shared buffer.
*/

#define MaxItems 5    // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5  // Size of the shared buffer

sem_t empty;         // Semaphore to track empty slots in the buffer
sem_t full;          // Semaphore to track full slots in the buffer
int in = 0;          // Index for the next position where a producer will insert an item
int out = 0;         // Index for the next position where a consumer will remove an item
int buffer[BufferSize]; // Shared buffer array
pthread_mutex_t mutex;  // Mutex for controlling access to critical sections

// Function for the producer thread
void *producer(void *pno)
{  
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce a random item

        sem_wait(&empty); // Wait until there is an empty slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the mutex for exclusive access

        buffer[in] = item; // Insert item into the buffer at the 'in' index
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize; // Move the 'in' index forward circularly

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&full); // Signal that there's a new item in the buffer
    }
}

// Function for the consumer thread
void *consumer(void *cno)
{  
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full); // Wait until there is a full slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the mutex for exclusive access

        int item = buffer[out]; // Remove the item from the buffer at the 'out' index
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize; // Move the 'out' index forward circularly

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&empty); // Signal that there's an empty slot in the buffer
    }
}

int main()
{  
    pthread_t pro[5], con[5]; // Thread arrays for producers and consumers
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex
    sem_init(&empty, 0, BufferSize);  // Initialize 'empty' semaphore to BufferSize (all slots empty)
    sem_init(&full, 0, 0);            // Initialize 'full' semaphore to 0 (no items in buffer)

    int a[5] = {1, 2, 3, 4, 5}; // Array used to identify each producer and consumer thread

    // Create 5 producer threads
    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }

    // Create 5 consumer threads
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    // Wait for all producer threads to finish
    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    // Wait for all consumer threads to finish
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    // Destroy the mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
