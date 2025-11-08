#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 20 // length of page reference string
#define MAX_FRAMES 7 // max frame size

// Function to generate random reference string
void generate_reference_string(int ref_string[], int n)
{
    for (int i = 0; i < n; i++)
        ref_string[i] = rand() % 10; // pages 0-9
}

// Function to display reference string
void display_reference_string(int ref_string[], int n)
{
    printf("\nPage Reference String:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", ref_string[i]);
    printf("\n");
}

// FIFO Page Replacement
int fifo(int ref_string[], int n, int frame_size)
{
    int frames[MAX_FRAMES];
    int page_faults = 0, index = 0;

    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nFIFO Simulation (Frame size = %d)\n", frame_size);
    for (int i = 0; i < n; i++)
    {
        int page = ref_string[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frames[index] = page;
            index = (index + 1) % frame_size;
            page_faults++;
        }

        printf("Step %2d | ", i + 1);
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf(found ? " | Hit\n" : " | Fault\n");
    }

    printf("Total Page Faults (FIFO): %d\n", page_faults);
    return page_faults;
}

// LRU Page Replacement
int lru(int ref_string[], int n, int frame_size)
{
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int page_faults = 0;

    for (int i = 0; i < frame_size; i++)
    {
        frames[i] = -1;
        last_used[i] = 0;
    }

    printf("\nLRU Simulation (Frame size = %d)\n", frame_size);
    for (int i = 0; i < n; i++)
    {
        int page = ref_string[i];
        int found = 0, replace_index = -1;

        // Check if page is already in frame
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                last_used[j] = i; // update recent use
                break;
            }
        }

        if (!found)
        {
            page_faults++;
            int min_time = 9999;

            // Find least recently used frame
            for (int j = 0; j < frame_size; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
                if (last_used[j] < min_time)
                {
                    min_time = last_used[j];
                    replace_index = j;
                }
            }

            frames[replace_index] = page;
            last_used[replace_index] = i;
        }

        printf("Step %2d | ", i + 1);
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf(found ? " | Hit\n" : " | Fault\n");
    }

    printf("Total Page Faults (LRU): %d\n", page_faults);
    return page_faults;
}

int main()
{
    srand(time(NULL));

    int ref_string[MAX_PAGES];
    int n = MAX_PAGES;

    generate_reference_string(ref_string, n);
    display_reference_string(ref_string, n);

    printf("\n=== Page Replacement Simulation ===\n");

    for (int frames = 1; frames <= 7; frames++)
    {
        printf("\n-----------------------------------");
        int fifo_faults = fifo(ref_string, n, frames);
        int lru_faults = lru(ref_string, n, frames);
        printf("Frame size %d → FIFO Faults = %d | LRU Faults = %d\n", frames, fifo_faults, lru_faults);
    }

    return 0;
}
