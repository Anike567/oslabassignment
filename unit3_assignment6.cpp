#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

size_t size = 10;
key_t key;

int main(void) {
    key = ftok("progfile", 65);

    if (key == -1) {
        cout << "Error generating key" << endl;
        return 1;
    }
    else{
        cout<<key<<endl;
    }

    int msgid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (msgid == -1) {
        cout << "Error occurred" << endl;
        return 1;
    }

    char *str = (char *)shmat(msgid, nullptr, 0);
    if (str == (char *)(-1)) {
        cout << "Error attaching shared memory" << endl;
        return 1;
    }

    cout << "Enter the message:" << endl;
    cin.getline(str, 1024);

    if (shmdt(str) == -1) {
        cout << "Error detaching shared memory" << endl;
        return 1;
    }

    if (shmctl(msgid, IPC_RMID, NULL) == -1) {
        cout << "Error deleting shared memory" << endl;
        return 1;
    }

    cout << "Data is written to shared memory" << endl;

    return 0;
}
