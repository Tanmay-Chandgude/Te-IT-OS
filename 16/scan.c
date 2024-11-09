//SCAN Disk Scheduling algorithm

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Comparator function for sorting the request queue
int comparator(const void * a, const void *b)
{
   int x =*(int *)a;   // Dereference the pointers to get the values
   int y =*(int *)b;
   if(x < y)
     return -1;  // If x < y, no change in order (for ascending sort)
   else if( x >= y) // If x >= y
    return 1;    // Swap positions (for ascending sort)
} 

// Function to find the minimum element in the request queue
int min_element(int request_queue[], int n)
{
    int min = INT_MAX;  // Initialize to maximum possible integer value
    for(int i = 0; i < n; i++)  // Traverse through the queue
    {
       if(request_queue[i] < min)
          min = request_queue[i];  // Update min if current element is smaller
    }
    return min;  
}

// Function to find the maximum element in the request queue
int max_element(int request_queue[], int n)
{
   int max = INT_MIN;  // Initialize to minimum possible integer value
   for(int i = 0; i < n; i++)  // Traverse through the queue
   {
      if(request_queue[i] > max)
          max = request_queue[i];  // Update max if current element is larger
   }
    return max;  
}

// Function to apply SCAN Disk Scheduling algorithm
int applySCANAlgo(int total_cylinders, int request_queue[], int initial_pos, 
                  int seek_sequence[], int direction, int *sequence_size, int n)
{
    int total_head_movement = 0, j = 0, k = 0;
    int left[n + 1], right[n + 1];  // Arrays to hold left and right side requests

    // Appending end values for scanning
    if(direction == 0)  // Moving to higher cylinder
    {
        if(initial_pos > min_element(request_queue, n))
     		right[j++] = total_cylinders - 1;  // Append highest cylinder
        right[j++] = initial_pos;
    }
    else if(direction == 1)  // Moving to lower cylinder
    {
        if(initial_pos < max_element(request_queue, n))
           left[k++] = 0;  // Append lowest cylinder
        left[k++] = initial_pos;
    }
   
    // Categorizing request queue elements to left and right based on current head position
    for (int i = 0; i < n; i++) {
        if (request_queue[i] < initial_pos)
            left[k++] = request_queue[i];  // Add to left side if less than initial position
        if (request_queue[i] > initial_pos)
            right[j++] = request_queue[i];  // Add to right side if greater than initial position
    }
   
    // Sorting left and right arrays
    qsort((void *)left, k, sizeof(int), comparator);  // Sort left array
    qsort((void *)right, j, sizeof(int), comparator);  // Sort right array

    // Run the scanning twice: once for right, then for left
    int completed = 2;
    while (completed--)  // Loop to scan in both directions
    {
        if (direction == 0)  // If moving right (higher cylinders)
        {
            for (int i = 0; i < j; i++)  // Traverse right array
            {
                total_head_movement += abs(initial_pos - right[i]);  // Calculate movement distance
                initial_pos = right[i];  // Update head position
                seek_sequence[*sequence_size] = right[i];  // Record in seek sequence
                (*sequence_size)++;
            }
            direction = 1;  // Reverse direction for the next scan
        }

        else if (direction == 1)  // If moving left (lower cylinders)
        {
            for (int i = k - 1; i >= 0; i--)  // Traverse left array in reverse
            {
                total_head_movement += abs(initial_pos - left[i]);  // Calculate movement distance
                initial_pos = left[i];  // Update head position
                seek_sequence[*sequence_size] = left[i];  // Record in seek sequence
                (*sequence_size)++;
            }
            direction = 0;  // Reverse direction for the next scan
        }
    }
    return total_head_movement;  // Return the total head movement
}

int main()
{
    int total_cylinders, total_head_movement = 0, initial_pos, n, direction, pos;
    
    // Taking inputs from the user
    printf("\nEnter the total no. of cylinders in HDD:\n");
    scanf("%d", &total_cylinders);

    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d", &n);
    
    int request_queue[n];
    int seek_sequence[n + 10];  // Size of seek sequence array (slightly larger than n)
    int sequence_size = 0;

    printf("\nEnter the cylinders no. in Request queue :\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &request_queue[i]);  // Input the request queue values

    // Input initial position of read-write head and the direction
    printf("\nEnter the initial Position of RW head: ");
    scanf("%d", &initial_pos);
    printf("\nEnter the direction in which Read Write head is moving:\n ");
    printf("\nEnter 0 if moving to higher cylinder else Enter 1: ");
    scanf("%d", &direction);

    // Check if the initial position is within valid range
    if(initial_pos < 0 || initial_pos > total_cylinders - 1)
    {
        printf("Wrong Initial Position Entered !!");
        exit(0);  // Exit if initial position is invalid
    }
    
    // Apply SCAN algorithm to get the total head movement and seek sequence
    total_head_movement = applySCANAlgo(total_cylinders, request_queue, initial_pos, 
                                        seek_sequence, direction, &sequence_size, n);
    
    // Output the results
    printf("\n\n*********** OUTPUT **********");
    printf("\nSeek Sequence: ");
    for(int i = 0; i < sequence_size; i++)
        printf("%d ", seek_sequence[i]);  // Print the seek sequence

    printf("\nTotal No. of Head Movements = %d\n", total_head_movement);
    printf("\nAverage head movements = %.2f\n\n", (float)total_head_movement / n);

    return 0;  // End of program
}
