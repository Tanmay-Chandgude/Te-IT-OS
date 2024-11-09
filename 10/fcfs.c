#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

void FCFS(int pages[], int n, int frames[], int frame_count) {
    int page_faults = 0;
    int page_hits = 0;
    int index = 0;

    printf("Page\tFrame Content\tPage Fault\n");

    for (int i = 0; i < n; i++) {
        int page_found = 0;

        // Check if the page is already in any of the frames
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                page_found = 1;
                page_hits++;
                break;
            }
        }

        // If page is not found in frames, it's a page fault
        if (!page_found) {
            frames[index] = pages[i];
            index = (index + 1) % frame_count; // Update index to replace the page in a circular manner
            page_faults++;
        }

        // Display the current state of frames and page fault status
        printf("%d\t", pages[i]);
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == -1)
                printf(" - ");
            else
                printf("%d ", frames[j]);
        }
        if (page_found)
            printf("\tPage Hit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    // Calculate and display the Page Fault and Hit ratios
    double page_fault_ratio = (double)page_faults / n;
    double page_hit_ratio = (double)page_hits / n;

    printf("\nTotal page faults: %d\n", page_faults);
    printf("Total page hits: %d\n", page_hits);
    printf("Page fault ratio: %.2f\n", page_fault_ratio);
    printf("Page hit ratio: %.2f\n", page_hit_ratio);
}

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, frame_count;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Getting page numbers
    printf("Enter the page numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Getting the frame size (minimum 3)
    do {
        printf("Enter the frame size (minimum 3): ");
        scanf("%d", &frame_count);
    } while (frame_count < 3);

    // Call FCFS page replacement function
    FCFS(pages, n, frames, frame_count);

    return 0;
}
