#include<iostream>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h> 
using namespace std;

int main(void){
    key_t key = ftok("progfile", 65);

    int msgid = shmget(key, 1024, 0666 | IPC_CREAT);
    if(msgid == -1){
        cout << "Error creating shared memory" << endl;
        return 1;
    }

    char *str = (char*)shmat(msgid, nullptr, 0);
    if (str == (char *)(-1)) {
        cout << "Error attaching shared memory" << endl;
        return 1;
    }

    cout << "Fetched data is: " << str << endl;

  
    if (shmdt(str) == -1) {
        cout << "Error detaching shared memory" << endl;
        return 1;
    }


    if (shmctl(msgid, IPC_RMID, NULL) == -1) {
        cout << "Error deleting shared memory" << endl;
        return 1;
    }

    return 0;
}
