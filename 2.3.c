#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to check if a number is prime
int isPrime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert string to integer

    if (n <= 0)
    {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child Process (PID: %d): Generating first %d prime numbers:\n", getpid(), n);

        int count = 0, num = 2;
        while (count < n)
        {
            if (isPrime(num))
            {
                printf("%d ", num);
                count++;
            }
            num++;
        }
        printf("\nChild process completed.\n");
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent Process (PID: %d): Child has finished execution.\n", getpid());
    }

    return 0;
}
