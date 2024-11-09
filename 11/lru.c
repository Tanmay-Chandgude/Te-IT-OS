#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

// Structure to represent each page in the page table
struct PageTable
{
    int frame_no;            // The frame number in which the page is stored
    int last_time_of_access; // Last time the page was accessed
    bool valid;              // Validity of the page (whether it's in the frame or not)
};

// Function to check if the referenced page is already in any frame or not
// Returns true if page is already present, otherwise returns false
bool isPagePresent(struct PageTable PT[], int page)
{
    if(PT[page].valid == 1)
       return true;  // Page is already in a frame
    return false;    // Page is not present in any frame
}

// Function to update the page table with the current state of a page
// Parameters: page (the page number), fr_no (frame number), 
// status (whether the page is valid or not), access_time (the current time of access)
void updatePageTable(struct PageTable PT[], int page, int fr_no, int status, int access_time)
{
    PT[page].valid = status;  // Set the validity of the page
    if(status == 1)  // If the page is valid (it was added to a frame)
    {
        PT[page].last_time_of_access = access_time;  // Update the access time
        PT[page].frame_no = fr_no;  // Set the frame number where the page is stored
    }
}

// Function to print the contents of the frame (the pages stored in the frames)
void printFrameContents(int frame[], int no_of_frames)
{
    for(int i = 0; i < no_of_frames; i++)
      printf("%d ", frame[i]);  // Print the page number in each frame
    printf("\n");
}

// Function to find the Least Recently Used (LRU) page in the frame
// The function will update the LRU_page_index to point to the page to be replaced
void searchLRUPage(struct PageTable PT[], int frame[], int no_of_frames, int *LRU_page_index)
{
    int min = INT_MAX;  // Initialize the minimum access time as the largest possible integer
    for(int i = 0; i < no_of_frames; i++)
    {
       // Find the page with the least recent access time (the LRU page)
       if(PT[frame[i]].last_time_of_access < min)
       {
           min = PT[frame[i]].last_time_of_access;
           *LRU_page_index = i;  // Update the index of the LRU page
       }
    }
}

int main()
{
    int i, n, no_of_frames, page_fault = 0, current = 0;
    bool flag = false;  // To track when frames are full
    printf("\n Enter the no. of pages:\n");
    scanf("%d", &n);  // Input the number of pages
    int reference_string[n];  // Create an array to store the reference string
    printf("\n Enter the reference string (different page numbers):\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &reference_string[i]);  // Input the reference string
    
    printf("\n Enter the no. of frames you want to give to the process: ");
    scanf("%d", &no_of_frames);  // Input the number of frames available for page storage
    
    int frame[no_of_frames];  // Create an array to store the frame contents
    memset(frame, -1, no_of_frames * sizeof(int));  // Initialize all frames with -1 (empty)
    
    struct PageTable PT[50];  // Create the page table for up to 50 pages
    for(int i = 0; i < 50; i++)
        PT[i].valid = 0;  // Set all pages as invalid initially
    
    printf("\n**** The Contents inside the Frame array at different time: ****\n");
    for(int i = 0; i < n; i++)  // Loop through the reference string
    {
        // Check if the page is already present in any frame
        if( !(isPagePresent(PT, reference_string[i])))
        {
            page_fault++;  // A page fault occurs since the page is not in the frame
            
            if(flag == false && current < no_of_frames)  // If frames are not yet full
            {
                frame[current] = reference_string[i];  // Add the page to the frame
                printFrameContents(frame, no_of_frames);  // Print the current contents of the frame
                updatePageTable(PT, reference_string[i], current, 1, i);  // Update the page table with this page
                
                current = current + 1;  // Move to the next frame
                
                if(current == no_of_frames)  // Once all frames are filled, set flag to true
                {
                    flag = true;
                }
            }
            else  // If frames are full, apply the LRU algorithm
            {
                int LRU_page_index;  // Index of the LRU page to be replaced
                searchLRUPage(PT, frame, no_of_frames, &LRU_page_index);  // Find the LRU page
                updatePageTable(PT, frame[LRU_page_index], -1 , 0, i);  // Mark the LRU page as invalid in the page table

                frame[LRU_page_index] = reference_string[i];  // Replace the LRU page with the new page
                printFrameContents(frame, no_of_frames);  // Print the current contents of the frame
                
                // Update the page table for the newly loaded page
                updatePageTable(PT, reference_string[i], LRU_page_index, 1, i); 
            }
        }
        PT[reference_string[i]].last_time_of_access = i;  // Update the access time for the current page
    }  // End of for loop
    
    // Print the results
    printf("\nTotal No. of Page Faults = %d\n", page_fault);
    printf("\nPage Fault Ratio = %.2f\n", (float)page_fault / n);
    printf("\nPage Hit Ratio = %.2f\n", (float)(n - page_fault) / n);
    
    return 0;  // Exit the program
}
