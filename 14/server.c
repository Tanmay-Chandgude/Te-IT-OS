#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE     27  // Define the size of shared memory to store 26 characters + null terminator

// Function to handle errors and terminate the program
void die(char *s)
{
    perror(s);  // Print the error message passed as parameter
    exit(1);    // Exit the program with an error code
}

int main()
{
    char c;       // Variable to store characters
    int shmid;    // Shared memory ID
    key_t key;    // Key for accessing shared memory
    char *shm, *s; // Pointer for shared memory and a temporary pointer for data manipulation

    key = 5679;   // Assign a fixed key for shared memory access

    // Create and get access to shared memory. If it doesn't exist, create it with the given permissions (0666)
    if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
        die("shmget");  // If shmget fails, call the die function to report error

    // Attach the shared memory segment to the process's address space
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");  // If shmat fails, call the die function to report error

    s = shm;  // Set the temporary pointer 's' to the shared memory address

    // Loop through the letters 'a' to 'z' and store them in shared memory
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;  // Store each character in shared memory and move to the next position

    // Print message indicating that the server is ready and data is available in shared memory
    printf("\n\nServer is Ready!!\n\nNow data is available on shared memory!!\n");

    /*
     * Waiting for other process
     * The server will continue to wait until it finds the '*' character in shared memory,
     * indicating that the other process has finished.
     */
    while (*shm != '*')  // Keep checking the shared memory for the '*' character
        sleep(1);         // Sleep for 1 second before checking again

    // Print message indicating that the server has terminated after receiving the signal
    printf("\n\nServer Terminated!!!\n\n");

    exit(0);  // Exit the program successfully
}
