//testa.c

#include<stdio.h>      // For input/output functions like printf and scanf
#include<stdlib.h>     // For functions like malloc, free, and exit
#include<string.h>     // For string manipulation functions like strcat and sprintf
#include<sys/types.h>  // For defining types like pid_t
#include<unistd.h>     // For fork(), execve(), and other system calls
#include<errno.h>      // For handling errors (e.g., perror)
#include<sys/wait.h>   // For waiting for child process completion (wait())

#define MAX 50         // Defines the maximum size for arrays

void main(int argc, char *argv[])
{
  int n;
  // Asking the user to input the number of elements they want to enter.
  printf("Enter the number of elements : ");
  scanf("%d", &n);  // Reading the number of elements from the user
  int arr[n];        // Declaring an array to hold 'n' elements
  
  pid_t pid;         // Variable to hold the process ID of the child process
  int status;        // Variable to hold the exit status of the child process
  char *newenviron[] = {NULL};  // Empty environment for the child process (execve uses this)
  char *newargv[20];  // Array to hold arguments for execve (which will execute a new program)
  char charArray[256];  // Array to store the concatenated string of array elements
  char temp[50];        // Temporary array to hold each integer as a string for concatenation
  
  charArray[0] = '\0';  // Initializing charArray to an empty string
  
  // Loop to read 'n' elements from the user and store them in the array
  for(int i = 0; i < n; i++)
  {
    printf("Enter element : ");
    scanf("%d", &arr[i]);  // Reading each integer and storing it in arr[]
  }

  // Loop to convert each element of the array to a string and concatenate them into charArray
  for(int i = 0; i < n; i++)
  {
    sprintf(temp, "%d", arr[i]);  // Convert each integer to a string and store it in temp
    strcat(charArray, temp);      // Concatenate temp to charArray
  }

  // Print the concatenated result of array elements as a string
  printf(" program 1 value of n %s \n", charArray);

  // Setting up new arguments for the execve call
  newargv[0] = argv[1];  // The first argument for execve, typically the program name
  newargv[1] = charArray; // The second argument, which contains the concatenated string of array elements
  newargv[2] = NULL;      // End of arguments for execve

  // Creating a new process using fork()
  pid = fork();  // Forking a new child process

  if (pid == -1)  // If fork fails
    printf("Error on fork\n");

  if (pid == 0)   // If we are in the child process (pid == 0)
  {
    // Child process executes the new program
    execve(argv[1], newargv, newenviron);  // Replaces the current process with the one specified in argv[1]
    // This statement will not be reached unless execve fails
    printf("execve is successfully executed");
  }
  else if (pid > 0)  // Parent process (pid > 0)
  {
    printf("Parent process\n");
    wait(&status);  // Parent waits for the child process to complete
  }
}
