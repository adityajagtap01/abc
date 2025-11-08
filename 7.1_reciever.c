





#sender


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;

    printf("Enter message type (integer): ");
    scanf("%ld", &message.msg_type);
    getchar();

    printf("Enter message text: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Message sent successfully.\n");

    return 0;
}













#reciever








#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;

    msgrcv(msgid, &message, sizeof(message.msg_text), 0, 0);

    for (int i = 0; message.msg_text[i]; i++)
    {
        message.msg_text[i] = toupper(message.msg_text[i]);
    }

    printf("Received Message (Uppercase): %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;

}
