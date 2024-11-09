// C Program to Implement the SSTF Disk Scheduling Algorithm

#include<stdio.h>
#include<stdlib.h> // for abs function to compute absolute values
#include<stdbool.h>  // for bool data type (true/false)
#include<limits.h>  // for INT_MAX (maximum value of an integer)
#include<string.h> // for memset function to initialize arrays

// Function to find and return the closest cylinder to the current position of RW head
int findclosestCylinder(int initial_pos, bool visited[], int request_queue[], int n)
{
  int min = INT_MAX, min_index = -1;  // Initialize minimum to max possible value and index to -1
  // Loop through all the request queue elements to find the closest unvisited cylinder
  for(int i = 0; i < n; i++)
  {
      // Check if cylinder has not been visited and is the closest to the initial position
      if(visited[i] == false && abs(initial_pos - request_queue[i]) < min)
      {
          min = abs(initial_pos - request_queue[i]);  // Update minimum distance
          min_index = i;  // Store the index of the closest cylinder
      }
  }
  return min_index;  // Return the index of the closest cylinder
}

// Function to apply the SSTF Disk Scheduling Algorithm
int applySSTFAlgo(int request_queue[], int initial_pos, bool visited[], int seek_sequence[], int n)
{
    int i = 0;            // Variable to index seek_sequence array
    int completed = 0, total_head_movement = 0;  // Initialize completed counter and total head movement counter
    // While not all cylinders are visited
    while(completed != n)
    {
      // Find the closest cylinder to the current position of RW head
      int min_index = findclosestCylinder(initial_pos, visited, request_queue, n);
      
      // Calculate the total head movement by adding the distance from current position to the closest cylinder
      total_head_movement += abs(initial_pos - request_queue[min_index]);
      initial_pos = request_queue[min_index];  // Update the RW head position to the new cylinder
      seek_sequence[i++] = request_queue[min_index];  // Record the cylinder in the seek sequence
      visited[min_index] = true;  // Mark the cylinder as visited to avoid re-visiting
      completed++;  // Increment completed request counter
    }
    
    return total_head_movement;  // Return the total head movement after all requests are completed
}

int main()
{
    int total_cylinders, total_head_movement, initial_pos, n;

    // *********** INPUT ********** 
    printf("\nEnter the total no. of cylinders in HDD:\n");
    scanf("%d", &total_cylinders);
    
    // Validate if the total cylinders are greater than 0
    if(total_cylinders <= 0) 
    {
      printf("Total Cylinders must be greater than 0");
      exit(0);  // Exit program if the input is invalid
    }
    
    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d", &n);

    int request_queue[n]; 
    int seek_sequence[n];

    printf("\nEnter the cylinders no. in Request queue :\n");
    for(int i = 0; i < n; i++)
     scanf("%d", &request_queue[i]);  // Input the cylinder numbers in the request queue
    
    printf("\nEnter the initial Position of RW head: ");
    scanf("%d", &initial_pos);  // Input the initial position of the RW head
    
    // Array to keep track of visited cylinders
    bool visited[n];        
    memset(visited, false, n * sizeof(bool));  // Initialize the visited array to false

    // Validate if the initial position is within the range of total cylinders
    if(initial_pos < 0 || initial_pos > total_cylinders - 1)
    {
        printf("Wrong Initial Position Entered !!");
        exit(0);  // Exit if the initial position is invalid
    }
    
    // Apply the SSTF Disk Scheduling Algorithm
    total_head_movement = applySSTFAlgo(request_queue, initial_pos, visited, seek_sequence, n);
    
    
    // *********** OUTPUT ********** 
    printf("\n\n*********** OUTPUT **********");
    printf("\nSeek Sequence: ");
    // Output the seek sequence (the order in which the cylinders are accessed)
    for(int i = 0; i < n; i++)
     printf("%d ", seek_sequence[i]);

    printf("\nTotal No. of Head Movements = %d\n", total_head_movement);  // Output total head movements
    printf("\nAverage head movements = %.2f\n\n", (float)total_head_movement / n);  // Output average head movements

    return 0;  // Exit the program
}
