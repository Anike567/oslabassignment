#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include<stdlib.h>


int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        char *arr[] = {"./execv", NULL};
        execv(arr[0], arr);
        perror("execv failed"); 
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            exit(1);
        }
        if (WIFEXITED(status)) {
            printf("child process exited with status %d \n",WEXITSTATUS(status));
        }

        else {
            printf("Child process exited abnormally \n");
        }
    }
    return 0;
}
