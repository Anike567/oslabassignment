#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h> 
    
    int main(void){
        int f;
        struct flock lck;

        f = open("file.txt", O_RDWR);
        if (f == -1) {
                perror("Failed to open file");
                return 1;
        }

        lck.l_type = F_WRLCK;
        lck.l_whence = SEEK_SET;
        lck.l_start = 0;
        lck.l_len = 0;
        lck.l_pid=getpid();
        int result1 = fcntl(f, F_GETLK, &lck);
        if (result1 == -1) {
                perror("Failed to get lock information");
                close(f);
        }

        if (lck.l_type != F_UNLCK) {
                printf("File is locked. Cannot read this now\n");
                printf("Lock type = %s\n", lck.l_type == F_RDLCK ? "read lock" : "write lock");
                printf("Lock owner pid: %d\n", lck.l_pid);
        }
        else{ 
                printf("file is not locked\n");
        }

        close(f);
        return 0;
    }
