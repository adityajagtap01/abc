#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(const char *label, int arr[], int n)
{
    printf("%s", label);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array: ");
    printArray("", arr, n);
    printf("-----------------------------------------\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // ---------------- ZOMBIE PROCESS DEMO ----------------
        // Uncomment this block to run zombie example

        /*
        printf("\n--- CHILD PROCESS (PID: %d) ---\n", getpid());
        insertionSort(arr, n);
        printArray("Child: Sorted Array: ", arr, n);
        printf("Child: Exiting immediately to become ZOMBIE.\n");
        exit(0);
        */

        // ---------------- ORPHAN PROCESS DEMO ----------------
        // Uncomment this block to run orphan example

        printf("\n--- CHILD PROCESS (PID: %d) ---\n", getpid());
        insertionSort(arr, n);
        printArray("Child: Sorted Array: ", arr, n);
        printf("Child: Sleeping 10 seconds to show ORPHAN state if parent exits early...\n");
        sleep(10);
        printf("Child: Woke up, current parent PID: %d\n", getppid());
        printf("Child: Exiting now.\n");
        exit(0);
    }

    else
    {
        // ---------------- ZOMBIE PROCESS DEMO ----------------
        // Uncomment this block to run zombie example

        /*
        printf("\n--- PARENT PROCESS (PID: %d) ---\n", getpid());
        printf("Parent: Created child with PID %d\n", pid);
        bubbleSort(arr, n);
        printArray("Parent: Sorted Array: ", arr, n);

        printf("\nParent: Sleeping 15 seconds...\n");
        printf("During this time, child (PID: %d) will be a ZOMBIE.\n", pid);
        printf("Run this in another terminal:\n");
        printf("ps -elf | grep %d\n", pid);

        sleep(15);

        printf("\nParent: Woke up, calling wait() to remove zombie.\n");
        wait(NULL);
        printf("Parent: Child process reaped (Zombie removed).\n");
        */

        // ---------------- ORPHAN PROCESS DEMO ----------------
        // Uncomment this block to run orphan example

        printf("\n--- PARENT PROCESS (PID: %d) ---\n", getpid());
        printf("Parent: Created child with PID %d\n", pid);
        bubbleSort(arr, n);
        printArray("Parent: Sorted Array: ", arr, n);
        printf("Parent: Exiting immediately — child will become ORPHAN.\n");
        exit(0);
    }

    return 0;
}
