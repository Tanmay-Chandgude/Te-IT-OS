#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void printFrames(int frames[], int frameCount) {
    printf("Frame Content: ");
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

int findOptimalPage(int pages[], int frames[], int frameCount, int currentIndex, int totalPages) {
    int farthest = -1;
    int replaceIndex = -1;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex + 1; j < totalPages; j++) {
            if (pages[j] == frames[i]) {
                break;
            }
        }
        if (j == totalPages) {
            return i;  // The page is not needed in future, so replace this frame
        }

        if (j > farthest) {
            farthest = j;
            replaceIndex = i;
        }
    }

    return replaceIndex;
}

void optimalPageReplacement(int pages[], int totalPages, int frameCount) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int pageHits = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < totalPages; i++) {
        int found = 0;

        // Check if the page is already in the frame (Page Hit)
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                pageHits++;
                break;
            }
        }

        // If page is not in frame, it's a Page Fault
        if (!found) {
            pageFaults++;
            int replaceIndex = -1;

            // Find the page to replace using Optimal Algorithm
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1) {
                replaceIndex = findOptimalPage(pages, frames, frameCount, i, totalPages);
            }

            // Replace the page in the frame
            frames[replaceIndex] = pages[i];
        }

        // Display current frame content
        printf("After accessing page %d:\n", pages[i]);
        printFrames(frames, frameCount);
    }

    // Calculate page fault ratio and page hit ratio
    float pageFaultRatio = (float)pageFaults / totalPages;
    float pageHitRatio = (float)pageHits / totalPages;

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
    printf("Page Fault Ratio: %.2f\n", pageFaultRatio);
    printf("Page Hit Ratio: %.2f\n", pageHitRatio);
}

int main() {
    int pages[MAX_PAGES];
    int totalPages, frameCount;

    // Input the number of pages and the page reference string
    printf("Enter the total number of pages: ");
    scanf("%d", &totalPages);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < totalPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the frame size (at least 3)
    do {
        printf("Enter the number of frames (at least 3): ");
        scanf("%d", &frameCount);
    } while (frameCount < 3);

    // Run the Optimal Page Replacement Algorithm
    optimalPageReplacement(pages, totalPages, frameCount);

    return 0;
}
