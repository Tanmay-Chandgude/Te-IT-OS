#include <stdio.h>      // Standard input-output header
// #include <limits.h>   // Uncomment if you need to use INT_MAX or INT_MIN
#include <stdbool.h>    // Boolean data type
#include <stdlib.h>     // Standard library for functions like qsort

// Structure to represent each process and its properties
struct process_struct {
    int pid;            // Process ID
    int at;             // Arrival Time
    int bt;             // Burst Time
    int ct, wt, tat, rt; // Completion Time, Waiting Time, Turn Around Time, Response Time
    int start_time;     // Start Time
    int bt_remaining;   // Remaining Burst Time (used for scheduling)
} ps[100];              // Array to hold up to 100 processes

// Function to find the maximum of two integers
int findmax(int a, int b) {
    return a > b ? a : b;
}

// Comparator function to sort processes by Arrival Time
int comparatorAT(const void *a, const void *b) {
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    return (x < y) ? -1 : 1;
}

// Comparator function to sort processes by Process ID
int comparatorPID(const void *a, const void *b) {
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    return (x < y) ? -1 : 1;
}

int main() {
    int n, index;                     // `n` = number of processes
    int cpu_utilization;              // CPU utilization calculation
    bool visited[100] = {false};      // Array to mark visited processes
    bool is_first_process = true;     // Flag to identify the first process
    int current_time = 0;             // Track the current time
    int max_completion_time;          // Max completion time for CPU utilization
    int completed = 0;                // Number of completed processes
    int tq, total_idle_time = 0;      // Time quantum and idle time tracking
    int length_cycle;                 // Total cycle length from first arrival to last completion
    int queue[100], front = -1, rear = -1; // Queue for Round Robin scheduling
    float sum_tat = 0, sum_wt = 0, sum_rt = 0; // Totals for calculating averages

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    // Input process details
    printf("\nEnter process Details: \n");
    for (int i = 0; i < n; ++i) {
        printf("Enter %dth process details: \n", i + 1);
        ps[i].pid = i + 1;           // Set process ID

        printf("\tEnter Arrival Time: ");
        scanf("%d", &ps[i].at);      // Input arrival time
        ps[i].pid = i;               // Set process ID to index for easy sorting

        printf("\tEnter Burst Time: ");
        scanf("%d", &ps[i].bt);      // Input burst time
        ps[i].bt_remaining = ps[i].bt; // Initialize remaining burst time to burst time
    }

    printf("\nEnter time quantum: ");
    scanf("%d", &tq);               // Input time quantum for Round Robin

    // Sort processes by arrival time
    qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);
    front = rear = 0;               // Initialize queue pointers
    queue[rear] = 0;                // Enqueue the first process
    visited[0] = true;              // Mark first process as visited

    // Main loop to execute Round Robin scheduling
    while (completed != n) {
        index = queue[front];       // Dequeue the next process
        front++;

        // Process has started for the first time
        if (ps[index].bt_remaining == ps[index].bt) {
            ps[index].start_time = findmax(current_time, ps[index].at); // Set start time
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;
        }

        // Execute process for time quantum or remaining time
        if (ps[index].bt_remaining - tq > 0) {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        } else {
            current_time += ps[index].bt_remaining; // Process completes
            ps[index].bt_remaining = 0;
            completed++;

            // Calculate completion time, TAT, WT, and RT for completed process
            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            // Accumulate total TAT, WT, RT for averages
            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }

        // Enqueue newly arrived processes that haven't been visited
        for (int i = 1; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) {
                queue[++rear] = i;
                visited[i] = true;
            }
        }

        // Re-enqueue current process if it still has remaining burst time
        if (ps[index].bt_remaining > 0)
            queue[++rear] = index;

        // If queue becomes empty, enqueue the next available process
        if (front > rear) {
            for (int i = 1; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    queue[rear++] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    // Calculate CPU utilization
    max_completion_time = 1e-9;
    for (int i = 0; i < n; i++)
        max_completion_time = findmax(max_completion_time, ps[i].ct);
    length_cycle = max_completion_time - ps[0].at;
    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    // Display process details and performance metrics
    qsort((void *)ps, n, sizeof(struct process_struct), comparatorPID); // Sort by process ID for display
    printf("\n\n====================================================================================\n");
    printf("\nProcess No.\tAT\tBT\tStart Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", i+1, ps[i].at, ps[i].bt, ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);

    printf("\n\n====================================================================================\n");
    printf("\nAverage Turn Around time= %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %.2f", (float)sum_wt / n);
    printf("\nAverage Response Time= %.2f\n", (float)sum_rt / n);

    return 0;
}
