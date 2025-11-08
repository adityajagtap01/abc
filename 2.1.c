#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort (Parent)
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort (Child)
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

// Print array
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
    printf("--------------------------------------------------\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    // ---------------- CHILD PROCESS ----------------
    else if (pid == 0)
    {
        printf("\n--- CHILD PROCESS (PID: %d) ---\n", getpid());
        printf("Child: Using Insertion Sort\n");

        insertionSort(arr, n);
        printArray("Child: Sorted Array: ", arr, n);

        printf("Child: Sleeping 10 seconds to show ORPHAN state if parent exits early...\n");
        sleep(10);
        printf("Child: Woke up, current parent PID: %d\n", getppid());
        printf("Child: Exiting now.\n");
        exit(0);
    }

    // ---------------- PARENT PROCESS ----------------
    else
    {
        printf("\n--- PARENT PROCESS (PID: %d) ---\n", getpid());
        printf("Parent: Created a child with PID %d\n", pid);
        printf("Parent: Using Bubble Sort\n");

        bubbleSort(arr, n);
        printArray("Parent: Sorted Array: ", arr, n);

        // --- ZOMBIE DEMONSTRATION ---
        printf("\nParent: Sleeping 10 seconds (child will finish and become ZOMBIE)...\n");
        printf("Run 'ps -elf | grep %d' in another terminal to see zombie state.\n", pid);
        sleep(10);

        printf("\nParent: Woke up, calling wait() to remove zombie.\n");
        wait(NULL);
        printf("Parent: Child process reaped (Zombie removed).\n");

        // --- ORPHAN DEMONSTRATION ---
        printf("\nParent: Sleeping 3 seconds, then exiting before child wakes up.\n");
        printf("After parent exits, run 'ps -elf | grep %d' to see child adopted by init.\n", pid);
        sleep(3);

        printf("Parent: Exiting now. Child will become orphan if still running.\n");
        exit(0);
    }

    return 0;
}
