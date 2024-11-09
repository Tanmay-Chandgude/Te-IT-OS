// Banker's Algorithm for Deadlock Avoidance
#include <stdio.h>

int main()
{
    // Define variables for number of processes (n) and resources (m)
    int n, m, i, j, k;
    
    // Get the number of processes from the user
    printf("\nEnter Number of processes: ");
    scanf("%d", &n);

    // Get the number of resources from the user
    printf("\nEnter Number of resources : ");
    scanf("%d", &m);

    // Declare matrices for allocation and maximum demand of each process
    int alloc[n][m];
    int max[n][m];

    // Input the allocation matrix from the user
    printf("\n\nEnter Details for Allocation matrix:(%dX%d) \n", n, m);
    for (int i = 0; i < n; i++)
    {
        printf("\n\tEnter %dth row: ", i + 1);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]); // Allocation matrix input for process i and resource j
        }
    }
    
    // Input the maximum demand matrix from the user
    printf("\n\nEnter Details for Max matrix:(%dX%d) \n", n, m);
    for (int i = 0; i < n; i++)
    {
        printf("\n\tEnter %dth row: ", i + 1);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]); // Max matrix input for process i and resource j
        }
    }

    // Input available resources
    int avail[m];
    printf("\n\nEnter Details for Available Resources:\n");
    for (int j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]); // Available instances of each resource
    }

    // Initialize arrays for tracking process completion and sequence
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0; // f[k] is 0 if process k has not finished yet
    }

    // Calculate the need matrix by subtracting allocation from max demand
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j]; // Need for process i and resource j
    }

    // Begin to find a safe sequence
    int y = 0;
    for (k = 0; k < m; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0) // Process i hasn't finished
            {
                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j]) // If resources are insufficient
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) // Resources are sufficient for process i
                {
                    ans[ind++] = i; // Add process i to the safe sequence
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y]; // Release resources from process i
                    f[i] = 1; // Mark process i as finished
                }
            }
        }
    }

    // Check if all processes could finish safely
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0) // If any process couldn't finish
        {
            flag = 0;
            printf("The following system is not safe");
            break;
        }
    }

    // If all processes could finish, print the safe sequence
    if (flag == 1)
    {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[n - 1]);
    }

    return 0; // End program
}
