#include <stdio.h>#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, tat, wt, completed;
};

void printResults(struct process p[], int n, const char *algo, int gantt[], int gcount) {
    float total_tat = 0, total_wt = 0;
    printf("\nResults for %s\n", algo);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("-----------------------------------\n");
    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT : %.2f\n", total_wt / n);

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gcount; i++) printf(" P%d |", gantt[i]);
    printf("\n");
}

void fcfs(struct process p[], int n) {
    struct process temp[20], t;
    int gantt[50], g = 0;
    for (int i = 0; i < n; i++) temp[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j].at > temp[j + 1].at) {
                t = temp[j]; temp[j] = temp[j + 1]; temp[j + 1] = t;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < temp[i].at) time = temp[i].at;
        time += temp[i].bt;
        temp[i].ct = time;
        gantt[g++] = temp[i].pid;
    }
    printResults(temp, n, "FCFS", gantt, g);
}

void sjf(struct process p[], int n) {
    struct process temp[20];
    int gantt[50], g = 0;
    for (int i = 0; i < n; i++) { temp[i] = p[i]; temp[i].completed = 0; }
    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, min_bt = 999;
        for (int i = 0; i < n; i++)
            if (temp[i].at <= time && !temp[i].completed && temp[i].bt < min_bt)
                { min_bt = temp[i].bt; idx = i; }

        if (idx == -1) time++;
        else {
            time += temp[idx].bt;
            temp[idx].ct = time;
            temp[idx].completed = 1;
            gantt[g++] = temp[idx].pid;
            completed++;
        }
    }
    printResults(temp, n, "SJF Non-Preemptive", gantt, g);
}

void round_robin(struct process p[], int n, int tq) {
    struct process temp[20];
    int rem_bt[20], gantt[100], g = 0;
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        rem_bt[i] = p[i].bt;
        temp[i].completed = 0;
    }
    int time = 0, done;

    while (1) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && temp[i].at <= time) {
                done = 0;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                    gantt[g++] = temp[i].pid;
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    temp[i].ct = time;
                    gantt[g++] = temp[i].pid;
                }
            }
        }
        if (done) break;
    }
    printResults(temp, n, "Round Robin", gantt, g);
}

int main() {
    int n, choice, tq;
    struct process proc[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

    while (1) {
        printf("\nCPU Scheduling Menu\n");
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. Round Robin\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) fcfs(proc, n);
        else if (choice == 2) sjf(proc, n);
        else if (choice == 3) {
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
            round_robin(proc, n, tq);
        }
        else if (choice == 4) exit(0);
        else printf("Invalid choice!\n");
    }
    return 0;
}

