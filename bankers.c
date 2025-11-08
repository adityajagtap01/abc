#include <stdio.h>

int main()
{
    int n, m; // n = number of processes, m = number of resources
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10], safeSeq[10];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Maximum Need Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    printf("\nEnter Available Resources for each type (%d): ", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    // Display Need matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    // Initialize finish array
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    // Banker's Algorithm
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int canExecute = 1;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute)
                {
                    // Process i can safely execute
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j]; // release resources

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("\nSystem is in an *UNSAFE STATE* — No safe sequence exists!\n");
            return 0;
        }
    }
    // If we reach here, system is safe
    printf("\nSystem is in a *SAFE STATE*.\nSafe Sequence: < ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf(">\n");
    return 0;
}