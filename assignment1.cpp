#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(void) {
    pid_t id = fork();

    if (id < 0) {
        perror("Error occurs");
    }
    else if (id == 0) {
        pid_t grand_child_id = fork();
        if (grand_child_id < 0) {
            perror("Error occurs");
        }
        else if (grand_child_id == 0) {
            cout <<"child id"<<getpid()<<"   parent id is"<<getppid()<<endl;
        }
        else {
            waitpid(grand_child_id, NULL, 0);
        }
        cout << "Process ID"<< getpid() <<"    Parent ID: "<<getppid() << endl;
    }
    else {
        waitpid(id, NULL, 0);
        cout << getpid() <<"    "<<getppid() << endl;
    }
    return 0;
}
