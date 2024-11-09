#include <stdio.h>
#include <stdbool.h>

// Define a structure for Process
struct Process
{
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tt;     // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
    int st;     // Start Time
};

int main()
{
    int size = 0;
    // Ask for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &size);

    struct Process ps[size]; // Declare an array of processes of size 'size'

    // Ask for the details of each process
    printf("\nEnter process Details: \n");
    for (int i = 0; i < size; ++i)
    {
        printf("Enter %dth process details: \n", i + 1);
        ps[i].pid = i + 1; // Assigning process ID

        // Getting Arrival Time and Burst Time from the user
        printf("\tEnter Arrival Time: ");
        scanf("%d", &ps[i].at);

        printf("\tEnter Burst Time: ");
        scanf("%d", &ps[i].bt);
    }

    int n = size;
    int completed = 0; // To track how many processes have completed
    int currentTime = 0; // Time starts at 0
    int burstTimeR[4]; // Temporary array to keep track of remaining burst time for each process
    bool iscompleted[4] = {false}; // To keep track of whether a process has completed or not

    // Variables to calculate average Waiting Time, Turnaround Time, and Response Time
    float avgWT = 0, avgTT = 0, avgRT = 0;

    // Copy burst times to burstTimeR array
    for (int i = 0; i < n; i++)
    {
        burstTimeR[i] = ps[i].bt;
    }

    // Loop to simulate the CPU scheduling process
    while (completed != n)
    {
        int minimum = 99999;
        int miniI = -1;

        // Find the process with the minimum burst time that is ready to execute (has arrived and is not completed)
        for (int i = 0; i < n; i++)
        {
            if ((ps[i].at <= currentTime) && (iscompleted[i] == false))
            {
                if (burstTimeR[i] < minimum)
                {
                    minimum = burstTimeR[i];
                    miniI = i;
                }
                // If two processes have the same burst time, choose the one with the earliest arrival time
                if (burstTimeR[i] == minimum)
                {
                    if (ps[i].at < ps[miniI].at)
                    {
                        minimum = burstTimeR[i];
                        miniI = i;
                    }
                }
            }
        }

        // If no process is ready to execute, increment the time
        if (miniI == -1)
        {
            currentTime++;
        }
        else
        {
            // If the process has started execution, record the start time
            if (burstTimeR[miniI] == ps[miniI].bt)
            {
                ps[miniI].st = currentTime;
            }

            // Decrease the remaining burst time of the selected process by 1 unit (simulating 1 unit of time)
            burstTimeR[miniI] -= 1;
            currentTime++; // Increment the current time by 1

            // If the process has completed, calculate its times and mark it as completed
            if (burstTimeR[miniI] == 0)
            {
                ps[miniI].ct = currentTime; // Completion Time
                ps[miniI].tt = ps[miniI].ct - ps[miniI].at; // Turnaround Time = Completion Time - Arrival Time
                ps[miniI].wt = ps[miniI].tt - ps[miniI].bt; // Waiting Time = Turnaround Time - Burst Time
                ps[miniI].rt = ps[miniI].st - ps[miniI].at; // Response Time = Start Time - Arrival Time

                // Accumulate the times for average calculations
                avgWT += ps[miniI].wt;
                avgTT += ps[miniI].tt;
                avgRT += ps[miniI].rt;

                completed++; // Increase completed count
                iscompleted[miniI] = true; // Mark process as completed
            }
        }
    }

    // Print the results in a tabular format
    printf("\n\n====================================================================================\n");
    printf("PID \t AT \t BT \t CT \t TAT \t WT \t RT \t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d \t %d \t %d \t %d \t %d \t %d \t %d \t\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tt, ps[i].wt, ps[i].rt);
    }
    printf("\n\n====================================================================================\n");

    // Print the average times for all processes
    printf("\n\n AVG WT: %f", avgWT / n);
    printf("\n\n AVG TAT: %f", avgTT / n);
    printf("\n\n AVG RT: %f", avgRT / n);
    printf("\n\n====================================================================================\n");
}
