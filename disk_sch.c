// lets start writing code for scan and look

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define MAX 499
#define MIN 0
int compare(const void *a, const void *b)
{

    return (*(int *)a - *(int *)b);
}
void run_scan(int head, int req[])
{

    int up[N];
    int down[N];
    int upcount = 0;
    int downcount = 0;
    int total = 0;
    int current = head;

    printf("\n..........SCAN (DIRECTION UP)...........\n");
    printf("Seek Seq :%d", head);

    for (int i = 0; i < N; i++)
    {
        if (req[i] >= head)
        {
            up[upcount++] = req[i];
        }
        else
        {
            down[downcount++] = req[i];
        }
    }

    qsort(up, upcount, sizeof(int), compare);
    qsort(down, downcount, sizeof(int), compare);

    // fill in up

    for (int i = 0; i < upcount; i++)
    {
        total += abs(up[i] - current);
        current = up[i];
        printf("->%d", current);
    }
    // IN SCAN

    total += abs(MAX - current);
    current = MAX;
    printf("->%d", MAX);
    // fill in down

    for (int i = downcount - 1; i >= 0; i--)
    {
        total += abs(down[i] - current);
        current = down[i];
        printf("->%d", current);
    }

    printf("\n------------------------------------------------\n");
    printf("Total Head Movement :%d \n", total);
    printf("Average seek %.2f\n:", (float)total / N);
}
void run_cScan(int head, int req[])
{

    int up[N];
    int down[N];
    int upcounter = 0;
    int downcounter = 0;
    int total = 0;
    int currrent = head;
    printf("..............C-SCAN SIMULATION------------\n");

    for (int i = 0; i < N; i++)
    {
        if (req[i] >= currrent)
        {
            up[upcounter++] = req[i];
        }
        else
        {
            down[downcounter++] = req[i];
        }
    }

    qsort(up, upcounter, sizeof(int), compare);
    qsort(down, downcounter, sizeof(int), compare);

    // up
    for (int i = 0; i < upcounter; i++)
    {
        total += abs(up[i] - currrent);
        currrent = up[i];
        printf("-> %d", currrent);
    }
    // till end

    total += abs(currrent - MAX);
    currrent = MAX;
    printf("->%d", currrent);

    // now to to direct start

    total += abs(currrent - MIN);
    currrent = MIN;
    printf("->%d ", currrent);

    // dowm

    for (int i = 0; i < downcounter; i++)
    {
        total += abs(currrent - down[i]);
        currrent = down[i];
        printf("->%d", currrent);
    }
    printf("\n------------------------------------------------\n");
    printf("Total Head Movement :%d \n", total);
    printf("Average seek %.2f\n:", (float)total / N);
}
void run_look(int head, int req[])
{

    int up[N];
    int down[N];
    int upcount = 0;
    int downcount = 0;
    int total = 0;
    int current = head;

    printf("\n..........LOOK (DIRECTION UP)...........\n");
    printf("Seek Seq :%d", head);

    for (int i = 0; i < N; i++)
    {
        if (req[i] >= head)
        {
            up[upcount++] = req[i];
        }
        else
        {
            down[downcount++] = req[i];
        }
    }

    qsort(up, upcount, sizeof(int), compare);
    qsort(down, downcount, sizeof(int), compare);

    // fill in up

    for (int i = 0; i < upcount; i++)
    {
        total += abs(up[i] - current);
        current = up[i];
        printf("->%d", current);
    }
    // IN SCAN

    for (int i = downcount - 1; i >= 0; i--)
    {
        total += abs(down[i] - current);
        current = down[i];
        printf("->%d", current);
    }

    printf("\n------------------------------------------------\n");
    printf("Total Head Movement :%d \n", total);
    printf("Average seek %.2f\n:", (float)total / N);
}
int main()
{
    int req[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};

    int head = 185;
    run_scan(head, req);
    run_look(head, req);
    run_cScan(head, req);
}