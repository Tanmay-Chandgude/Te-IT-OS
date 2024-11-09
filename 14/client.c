// Client Program to read from shared memory

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE     27  // Maximum size of the shared memory segment

// Function to handle errors and exit the program
void die(char *s)
{
    perror(s);  // Prints error message passed as argument
    exit(1);    // Exits the program with status 1 (indicating error)
}

int main()
{
    int shmid;         // Shared memory ID
    key_t key;         // Key for accessing shared memory
    char *shm, *s;     // Pointer for shared memory and loop variable for reading

    key = 5679;    // The key to access shared memory (it must be the same for both client and server)
 
    // Access the shared memory segment with the specified key and size
    // 0666 is the permissions setting allowing read and write access
    if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)
        die("shmget");  // If shmget fails, print the error message and exit
 
    // Attach the shared memory segment to the client's address space
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");  // If shmat fails, print the error message and exit
    
    // Print a message indicating that the client has started reading
    printf("\n\nClient started reading\n\n");

    // Loop through the shared memory to print its contents
    // Reads character by character from the shared memory until the null terminator
    for (s = shm; *s != '\0'; s++)
    {
        putchar(*s);  // Output each character from shared memory
        printf("\t"); // Add a tab for formatting
    }
    putchar('\n');  // Print a newline after reading all characters

    // Change the first byte in the shared memory to '*' to signal the server
    *shm = '*'; 

    // Print a message indicating that the client has terminated
    printf("\n\nClient Terminated!!!\n\n");

    exit(0);  // Exit the program successfully
}
