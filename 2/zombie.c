#include <stdio.h>      // Standard input-output header for printf
#include <sys/types.h>  // Header for data types used in system calls
#include <sys/wait.h>   // Header for waiting on processes
#include <stdlib.h>     // Header for general utilities like exit()
#include <unistd.h>     // Header for UNIX standard functions, like fork(), getpid(), getppid(), sleep()

// Function to perform bubble sort
void bubbleSort(int array[], int size) {
    for (int step = 0; step < size - 1; ++step) {    // Iterate over the array
        for (int i = 0; i < size - step - 1; ++i) {  // Perform pair-wise comparison
            if (array[i] > array[i + 1]) {           // Swap if the current element is greater than the next
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

// Function to print the array after bubble sort
void printArray_bubble(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);  // Print each element
    }
}

// Helper function to swap two elements (used in quick sort)
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for quicksort algorithm
int partition(int array[], int low, int high) {
    int pivot = array[high];  // Set the pivot element
    int i = (low - 1);        // Index of smaller element
    
    for (int j = low; j < high; j++) {  // Iterate through the array
        if (array[j] <= pivot) {        // Check if the current element is <= pivot
            i++;
            swap(&array[i], &array[j]); // Swap if condition is met
        }
    }
    swap(&array[i + 1], &array[high]);  // Place pivot in its correct position
    return (i + 1);                     // Return the partition index
}

// Quick sort function
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high); // Find partition index
        quickSort(array, low, pi - 1);        // Recursively sort elements before partition
        quickSort(array, pi + 1, high);       // Recursively sort elements after partition
    }
}

// Function to print the array after quicksort
void printArray_quick(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);  // Print each element
    }
    printf("\n");
}

// Main function
void main() {
    int data[] = {8, 5, 7, 6, 3};               // Initialize an array
    int size = sizeof(data) / sizeof(data[0]);  // Calculate the size of the array
    int pid, status;
    
    pid = fork();  // Create a new process (forking)
    
    if (pid == 0) {  // Child process
        printf("\n Welcome to child process");
        printf("\n Child process id %d \n", getpid());    // Print child process ID
        printf("\n Child's parent process id %d \n", getppid()); // Print parent ID of the child
        
        printf("\n Unsorted Array : ");
        printArray_quick(data, size);  // Display unsorted array
        bubbleSort(data, size);        // Perform bubble sort
        
        printf(" Bubble Sort :: Sorted Array in Ascending Order : ");
        printArray_bubble(data, size); // Print sorted array using bubble sort
        printf("\n\n");
    } 
    else if (pid != 0) {  // Parent process
        printf("\n");
        sleep(5);                  // Sleep to ensure child process executes first
        system("ps -aux");         // List all running processes
        printf("\n Welcome to Parent process");
        printf("\n Parent process id %d \n", getpid());   // Print parent process ID
        
        printf("\n Unsorted Array : ");
        printArray_quick(data, size);    // Display unsorted array
        quickSort(data, 0, size - 1);    // Perform quicksort
        
        printf(" Quick sort :: Sorted array in ascending order : ");
        printArray_quick(data, size);    // Print sorted array using quicksort
    }
}
