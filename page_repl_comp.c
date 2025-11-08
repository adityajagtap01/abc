#include <stdio.h>

void printFrames(int frames[], int frameSize, int page, int fault)
{
    printf("%d:[", page);
    for (int i = 0; i < frameSize; i++)
    {
        if (frames[i] == -1)
            printf(".");
        else
            printf("%d", frames[i]);
    }
    printf("]");
    if (fault)
        printf(" Page Fault\n");
    else
        printf(" Page Hit\n");
}

/* ---------------- FIFO ---------------- */
void run_fcfs(int string_ref[], int n, int frameSize)
{
    int frames[frameSize];
    int oldIndex = 0;
    int page_fault = 0;

    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement Simulation (Frame size = %d) ---\n", frameSize);

    for (int i = 0; i < n; i++)
    {
        int page = string_ref[i];
        int found = 0;

        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            printFrames(frames, frameSize, page, 0);
        }
        else
        {
            page_fault++;
            frames[oldIndex] = page;
            oldIndex = (oldIndex + 1) % frameSize;
            printFrames(frames, frameSize, page, 1);
        }
    }

    printf("------------------------------------------\n");
    printf("Total Page Faults: %d\n", page_fault);
    printf("Total Page Hits  : %d\n", n - page_fault);
}

/* ---------------- LRU ---------------- */
void run_lru(int string_ref[], int n, int frameSize)
{
    int frames[frameSize];
    int last_use_time[frameSize];
    int page_fault = 0;

    for (int i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        last_use_time[i] = -1;
    }

    printf("\n--- LRU Page Replacement Simulation (Frame size = %d) ---\n", frameSize);

    for (int i = 0; i < n; i++)
    {
        int page = string_ref[i];
        int found = 0, found_ind = -1;

        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                found_ind = j;
                break;
            }
        }

        if (found)
        {
            last_use_time[found_ind] = i;
            printFrames(frames, frameSize, page, 0);
        }
        else
        {
            page_fault++;
            int replace_index = -1;

            // Check for empty frame
            for (int j = 0; j < frameSize; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
            }

            // If no empty frame, find least recently used
            if (replace_index == -1)
            {
                int min_time = last_use_time[0];
                replace_index = 0;

                for (int j = 1; j < frameSize; j++)
                {
                    if (last_use_time[j] < min_time)
                    {
                        min_time = last_use_time[j];
                        replace_index = j;
                    }
                }
            }

            frames[replace_index] = page;
            last_use_time[replace_index] = i;
            printFrames(frames, frameSize, page, 1);
        }
    }

    printf("------------------------------------------\n");
    printf("Total Page Faults: %d\n", page_fault);
    printf("Total Page Hits  : %d\n", n - page_fault);
}

/* ---------------- OPTIMAL ---------------- */
void run_optimal(int string_ref[], int n, int frameSize)
{
    int frames[frameSize];
    int page_fault = 0;

    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\n--- OPTIMAL Page Replacement Simulation (Frame size = %d) ---\n", frameSize);

    for (int i = 0; i < n; i++)
    {
        int page = string_ref[i];
        int found = 0;

        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            printFrames(frames, frameSize, page, 0);
        }
        else
        {
            page_fault++;
            int replace_index = -1;

            // Check for empty frame
            for (int j = 0; j < frameSize; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
            }

            // If no empty frame, choose optimal replacement
            if (replace_index == -1)
            {
                int farthest = -1;
                int farthest_index = -1;

                for (int j = 0; j < frameSize; j++)
                {
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == string_ref[k])
                            break;
                    }

                    // If not found again, replace this
                    if (k == n)
                    {
                        farthest_index = j;
                        break;
                    }

                    if (k > farthest)
                    {
                        farthest = k;
                        farthest_index = j;
                    }
                }

                replace_index = farthest_index;
            }

            frames[replace_index] = page;
            printFrames(frames, frameSize, page, 1);
        }
    }

    printf("------------------------------------------\n");
    printf("Total Page Faults: %d\n", page_fault);
    printf("Total Page Hits  : %d\n", n - page_fault);
}

/* ---------------- MAIN ---------------- */
int main()
{
    int ref_string[] = {1, 2, 3, 4, 1, 2, 5, 1, 1, 2, 3, 4, 5};
    int n = 13;

    printf("Page Replacement Algorithms Simulation\n");

    run_fcfs(ref_string, n, 4);
    run_lru(ref_string, n, 3);
    run_optimal(ref_string, n, 3);

    return 0;
}
