#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define max 10

struct msg_buffer {
    long mes_type;
    char mes_text[100];
} message;

int main() {
    key_t key;
    int msg_id;

    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.mes_type = 1;
    while(1){
        printf("Enter the message\n");

        fgets(message.mes_text, max, stdin);

        msgsnd(msg_id, &message, sizeof(message), 0);
        printf("Data sent: %s", message.mes_text);
        sleep(2);
    }
    return 0;
}
