#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include<stdlib.h>

#define max 10

key_t key;
int msg_id;

struct msg_buffer {
    long mes_type;
    char mes_text[100];
};

void handleintr(int sig) {
    if (sig == SIGINT) {
        msgctl(msg_id, IPC_RMID, NULL);
        printf("Message queue removed.\n");
        exit(0);
    }
}

int main(void) {
    struct msg_buffer message; 

    signal(SIGINT, handleintr);

    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);

    while(1) {
        msgrcv(msg_id, &message, sizeof(message), 1, 0); 
        printf("Received data is: \n%s", message.mes_text);
        sleep(2);
    }
    return 0;
}
