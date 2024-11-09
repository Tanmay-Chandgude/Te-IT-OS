// Wait demo on Zombie state

#include <stdio.h>      // For standard input-output functions
#include <sys/types.h>  // For data types used in system calls
#include <sys/wait.h>   // For wait() function to manage process state
#include <stdlib.h>     // For general utilities, including memory allocation and process control
#include <unistd.h>     // For fork() and other process control functions

// Function to perform bubble sort on an array
void bubbleSort(int array[], int size)
{
    // Loop through each element in the array
    for (int step = 0; step < size - 1; ++step)
    {
        for (int i = 0; i < size - step - 1; ++i)
        {
            // If current element is greater than the next, swap them
            if (array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

// Function to print elements of an array for bubble sort results
void printArray_bubble(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
}

// Function to swap two integers (used in quick sort)
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for quick sort (selects a pivot and partitions array around it)
int partition(int array[], int low, int high)
{
    int pivot = array[high]; // Set last element as pivot
    int i = (low - 1);       // Index of smaller element

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than or equal to pivot
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    // Swap pivot element with the element at index i+1
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

// Function to perform quick sort on an array
void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high); // Get partitioning index
        quickSort(array, low, pi - 1);        // Recursively sort elements before partition
        quickSort(array, pi + 1, high);       // Recursively sort elements after partition
    }
}

// Function to print elements of an array for quick sort results
void printArray_quick(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int data[] = {8, 5, 7, 6, 3};           // Array to be sorted
    int size = sizeof(data) / sizeof(data[0]); // Calculate size of array

    int pid, status;
    pid_t w1;
    pid = fork();                           // Fork a new process

    if (pid == 0) // Child process
    {
        printf("\n Welcome to child process");
        printf("\n Child process id %d \n", getpid());
        printf("\n Child's parent process id %d \n", getppid());

        printf("\n Unsorted Array : ");
        printArray_quick(data, size);        // Print the unsorted array in child
        bubbleSort(data, size);              // Perform bubble sort

        printf(" Bubble Sort :: Sorted Array in Ascending Order : ");
        printArray_bubble(data, size);       // Print the sorted array in child
        printf("\n\n");
    }
    else if (pid != 0) // Parent process
    {
        w1 = wait(&status);                  // Wait for child process to finish
        printf("\n Status is %d \n", WEXITSTATUS(status)); // Print child exit status
        printf(" Return value of wait, w1=%d \n", w1);

        printf("\n");
        sleep(5);                            // Sleep to demonstrate zombie state
        system("ps -aux");                   // Display process status; child process becomes a zombie briefly

        printf("\n Welcome to Parent process");
        printf("\n parent process id %d \n", getpid());

        printf("\n Unsorted Array : ");
        printArray_quick(data, size);        // Print the unsorted array in parent
        quickSort(data, 0, size - 1);        // Perform quick sort

        printf(" Quick sort :: Sorted array in ascending order : ");
        printArray_quick(data, size);        // Print the sorted array in parent
    }
}

