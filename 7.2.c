#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *msg = (char *)shmat(shmid, NULL, 0);

    printf("Enter message: ");
    fgets(msg, 1024, stdin);
    msg[strcspn(msg, "\n")] = '\0'; // remove newline
    printf("Message written to shared memory.\n");

    // Don’t delete memory immediately — let client read it first
    shmdt(msg);

    return 0;
}

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666);
    char *msg = (char *)shmat(shmid, NULL, 0);

    printf("Data read from shared memory: %s\n", msg);

    shmdt(msg);
    shmctl(shmid, IPC_RMID, NULL); // Now remove after reading
    return 0;
}
