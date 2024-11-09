//LOOK Disk Scheduling algorithm

#include<stdio.h>
#include<stdlib.h>

// Comparator function to sort the array in ascending order
int comparator(const void * a, const void *b)
{
   int x =*(int *)a;  // Dereference pointers to get the values
   int y =*(int *)b;  
   if(x<y)
     return -1;  // Return negative to keep order
   else if( x>=y)  // = is for stable sorting, ensures consistent results
    return 1;    // Return positive to swap elements
} 

// Function to apply the SCAN algorithm
int applySCANAlgo(int total_cylinders, int request_queue[], int initial_pos, int seek_sequence[], int direction, int *sequence_size, int n)
{
    int total_head_movement=0, j=0, k=0;
    int left[n], right[n];

    // Distribute the request queue elements into left and right arrays based on their position relative to the initial head position
    if (direction == 0)  // Moving towards higher cylinders
        right[j++] = initial_pos;
    else if (direction == 1)  // Moving towards lower cylinders
        left[k++] = initial_pos;   
    
    for (int i = 0; i < n; i++) {
        if (request_queue[i] < initial_pos)  // Add smaller requests to left
            left[k++] = request_queue[i];
        if (request_queue[i] > initial_pos)  // Add larger requests to right
            right[j++] = request_queue[i];
    }
   
    // Sort both left and right arrays in ascending order
    qsort((void *)left, k, sizeof(int), comparator);
    qsort((void *)right, j, sizeof(int), comparator);
    

    // Run the SCAN algorithm by scanning both left and right of the head
    int completed = 2;
    while (completed--)
    {
        if (direction == 0)  // Moving towards higher cylinders
        {
            for (int i = 0; i < j; i++) 
            {
                // Calculate absolute distance moved
                total_head_movement += abs(initial_pos - right[i]);	
                initial_pos = right[i];
                // Add the current track to the seek sequence
                seek_sequence[*sequence_size] = right[i]; 
                (*sequence_size)++;
            }
            direction = 1;  // Change direction to left after reaching the farthest right cylinder
        }

        else if (direction == 1)  // Moving towards lower cylinders
        {
            for (int i = k - 1; i >= 0; i--) 
            {
                // Calculate absolute distance moved
                total_head_movement += abs(initial_pos - left[i]);	
                initial_pos = left[i];
                // Add the current track to the seek sequence
                seek_sequence[*sequence_size] = left[i]; 
                (*sequence_size)++;
            }
            direction = 0;  // Change direction to right after reaching the farthest left cylinder
        }
    }

    // Return the total head movement
    return total_head_movement;
}

int main()
{
    int total_cylinders, total_head_movement = 0, initial_pos, n, direction, pos;

    // Input the total number of cylinders in the HDD
    printf("\nEnter the total no. of cylinders in HDD:\n");
    scanf("%d", &total_cylinders);

    // Input the number of cylinders in the request queue
    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d", &n);
    
    int request_queue[n];  // Declare the request queue array
    int seek_sequence[n + 10];   // Array to hold the seek sequence (size slightly larger to accommodate extra elements)
    int sequence_size = 0;  // Variable to keep track of the size of the seek sequence

    // Input the cylinder numbers into the request queue
    printf("\nEnter the cylinders no. in Request queue :\n");
    for(int i = 0; i < n; i++)
     scanf("%d", &request_queue[i]);

    // Input the initial position of the read/write head
    printf("\nEnter the initial Position of RW head: ");
    scanf("%d", &initial_pos);

    // Input the direction in which the head is moving: 0 for moving towards higher cylinders, 1 for lower cylinders
    printf("\nEnter the direction in which Read Write head is moving:\n ");
    printf("\nEnter 0 if moving to higher cylinder else Enter 1: ");
    scanf("%d", &direction);

    // Check if the initial position is valid
    if(initial_pos < 0 || initial_pos > total_cylinders - 1)
    {
        printf("Wrong Initial Position Entered !!");
        exit(0);
    }
    
    // Call the function to apply the SCAN algorithm
    total_head_movement = applySCANAlgo(total_cylinders, request_queue, initial_pos, seek_sequence, direction, &sequence_size, n);
    
    // *********** OUTPUT ********** 
    printf("\n\n*********** OUTPUT **********");
    // Display the seek sequence
    printf("\nSeek Sequence: ");
    for(int i = 0; i < sequence_size; i++)
     printf("%d ", seek_sequence[i]);

    // Display total head movements and average head movements
    printf("\nTotal No. of Head Movements = %d\n", total_head_movement);
    printf("\nAverage head movements = %.2f\n\n", (float)total_head_movement / n);

    return 0;
}
