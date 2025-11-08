
// parent
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void sortArray(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    sortArray(arr, n);
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child Process
        char *args[n + 3]; // "child", array elements, search value, NULL

        args[0] = "./child"; // name of program to exec
        for (int i = 0; i < n; i++)
        {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }

        // Ask user for search element
        char *search = malloc(10);
        printf("Enter element to search: ");
        scanf("%s", search);

        args[n + 1] = search;
        args[n + 2] = NULL; // execve requires NULL termination

        execve("./child", args, NULL);
        perror("execve failed");
    }
    else
    {
        wait(NULL);
        printf("Parent process finished.\n");
    }

    return 0;
}

// child.c
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int n = argc - 2; // last arg is key
    int arr[n];

    for (int i = 1; i <= n; i++)
        arr[i - 1] = atoi(argv[i]);

    int key = atoi(argv[argc - 1]);

    printf("Child process received sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nSearching for %d...\n", key);

    int pos = binarySearch(arr, n, key);

    if (pos != -1)
        printf("Element %d found at position %d\n", key, pos + 1);
    else
        printf("Element %d not found in the array\n", key);

    return 0;
}
