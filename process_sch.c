#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

void printResults(struct process p[], int n, const char *algoName)
{
    float total_tat = 0.0;
    float total_wt = 0.0;

    printf("\nResults for %s\n", algoName);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf(".......................................\n");

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf(".................................................\n");
    printf("Average Turn Around Time : %.2f\n", total_tat / n);
    printf("Average Waiting Time : %.2f\n", total_wt / n);
}

void run_fcfs(struct process p[], int n)
{
    struct process temp_p[20], temp_swap;
    for (int i = 0; i < n; i++)
        temp_p[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp_p[j].at > temp_p[j + 1].at)
            {
                temp_swap = temp_p[j];
                temp_p[j] = temp_p[j + 1];
                temp_p[j + 1] = temp_swap;
            }

    int currenttime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currenttime < temp_p[i].at)
            currenttime = temp_p[i].at;

        temp_p[i].ct = currenttime + temp_p[i].bt;
        currenttime = temp_p[i].ct;
    }

    printResults(temp_p, n, "FCFS");
}

void sjf(struct process p[], int n)
{
    int currenttime = 0, completed_process = 0;
    struct process temp_p[20];

    for (int i = 0; i < n; i++)
    {
        temp_p[i] = p[i];
        temp_p[i].completed = 0;
    }

    while (completed_process < n)
    {
        int shortest_job_ind = -1;
        int shortest_bt = 999;

        for (int i = 0; i < n; i++)
            if (temp_p[i].at <= currenttime && temp_p[i].completed == 0 && temp_p[i].bt < shortest_bt)
            {
                shortest_bt = temp_p[i].bt;
                shortest_job_ind = i;
            }

        if (shortest_job_ind == -1)
        {
            int next_arrival = 9999;
            for (int i = 0; i < n; i++)
                if (temp_p[i].completed == 0 && temp_p[i].at < next_arrival)
                    next_arrival = temp_p[i].at;

            currenttime = next_arrival;
        }
        else
        {
            int i = shortest_job_ind;
            temp_p[i].ct = currenttime + temp_p[i].bt;
            currenttime = temp_p[i].ct;
            temp_p[i].completed = 1;
            completed_process++;
        }
    }

    printResults(temp_p, n, "SJF Non-Premptive");
}

void round_robin(struct process p[], int n, int tq)
{
    struct process temp_p[20];
    int rem_bt[20];
    int currenttime = 0, completed = 0;

    for (int i = 0; i < n; i++)
    {
        temp_p[i] = p[i];
        rem_bt[i] = p[i].bt;
        temp_p[i].completed = 0;
    }

    while (completed < n)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0 && temp_p[i].at <= currenttime)
            {
                done = 0;
                if (rem_bt[i] > tq)
                {
                    currenttime += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    currenttime += rem_bt[i];
                    rem_bt[i] = 0;
                    temp_p[i].ct = currenttime;
                    temp_p[i].completed = 1;
                    completed++;
                }
            }
        }

        if (done)
        {
            int next_arrival = 9999;
            for (int i = 0; i < n; i++)
                if (rem_bt[i] > 0 && temp_p[i].at < next_arrival)
                    next_arrival = temp_p[i].at;
            if (next_arrival != 9999)
                currenttime = next_arrival;
        }
    }

    printResults(temp_p, n, "Round Robin");
}

int main()
{
    int n, choice, tq;
    struct process proc[20];
    printf("ENTER THE NUMBER OF PROCESS::\n");
    scanf("%d", &n);

    printf("Enter the Process Details (AT = Arrival Time, BT = Burst Time):\n");
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Process P%d AT: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Process P%d BT: ", i + 1);
        scanf("%d", &proc[i].bt);
        proc[i].completed = 0;
    }

    while (1)
    {
        printf("\n..............................................\n");
        printf("CPU Scheduling Menu\n");
        printf("1. FCFS\n");
        printf("2. SJF (Non-Premptive)\n");
        printf("3. Round Robin\n");
        printf("4. Exit\n");
        printf("..............................................\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            run_fcfs(proc, n);
            break;
        case 2:
            sjf(proc, n);
            break;
        case 3:
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
            round_robin(proc, n, tq);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}
