#include <stdio.h>        // Standard Input Output library for printf function
#include <sys/types.h>    // Library for data types used in system calls
#include <sys/wait.h>     // Library for wait functions used in process handling
#include <stdlib.h>       // Standard library for general purpose functions
#include <unistd.h>       // Library for fork and process functions

// Bubble Sort function
void bubbleSort(int array[], int size) {
    // Outer loop to control the number of passes
    for (int step = 0; step < size - 1; ++step) {
        // Inner loop for comparing adjacent elements
        for (int i = 0; i < size - step - 1; ++i) {
            // Swap if the element is greater than the next element
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

// Function to print array elements for Bubble Sort
void printArray_bubble(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);  // Print each element
    }
}

// Swap function for Quick Sort
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for Quick Sort
int partition(int array[], int low, int high) {
    int pivot = array[high];  // Set the pivot as the last element
    int i = (low - 1);        // Pointer for greater element
    // Iterate through the array and rearrange elements based on pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;              // Increment the pointer
            swap(&array[i], &array[j]);  // Swap elements
        }
    }
    swap(&array[i + 1], &array[high]);  // Swap pivot to correct position
    return (i + 1);                     // Return pivot index
}

// Quick Sort function
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);  // Partition index
        // Recursively sort elements before and after partition
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Function to print array elements for Quick Sort
void printArray_quick(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);  // Print each element
    }
    printf("\n");
}

// Main function
void main() {
    int data[] = {8, 5, 7, 6, 3};  // Array of elements to be sorted
    int size = sizeof(data) / sizeof(data[0]);  // Calculate the size of the array
    int pid, status;
    pid = fork();  // Create a new process

    // Child process
    if (pid == 0) {
        printf("\n Child's parent process id %d \n", getppid());  // Print parent process ID
        sleep(3);  // Delay for 3 seconds
        printf("\n Welcome to child process \n");
        printf("\n Child process id %d \n", getpid());  // Print child process ID
        printf("\n Child's parent process id %d \n", getppid());

        printf("\n Unsorted Array : ");
        printArray_quick(data, size);  // Print unsorted array
        bubbleSort(data, size);  // Apply Bubble Sort

        printf(" Bubble Sort :: Sorted Array in Ascending Order : ");
        printArray_bubble(data, size);  // Print sorted array after Bubble Sort
        printf("\n\n");
    }
    // Parent process
    else if (pid != 0) {
        printf("\n Welcome to Parent process \n");
        printf("\n parent process id %d \n", getpid());  // Print parent process ID

        printf("\n Unsorted Array : ");
        printArray_quick(data, size);  // Print unsorted array
        quickSort(data, 0, size - 1);  // Apply Quick Sort

        printf(" Quick sort :: Sorted array in ascending order : ");
        printArray_quick(data, size);  // Print sorted array after Quick Sort
    }
}
