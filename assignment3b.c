#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int main(void) {
    sleep(1);
    int fd;
    struct flock lock, save_lock;

    fd = open("file.txt", O_RDWR);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid=getpid();

    int result = fcntl(fd, F_GETLK, &lock);
    if (result == -1) {
        perror("Failed to get lock information");
        close(fd);
        return 1;
    }
    printf(
    else if (lock.l_type != F_UNLCK) {
        result = fcntl(fd, F_SETLK, &lock);
        printf("locked \n");
        if (result == -1) {
            perror("Unable to set the lock");
        } 
        else {
                
            printf("File is locked. Cannot read this now\n");
            printf("Lock type = %s\n", lock.l_type == F_RDLCK ? "read lock" : "write lock");
            printf("Lock owner pid: %d\n", lock.l_pid);
        }
    }
    else{
        printf("not eter\n");
     }

    

    close(fd);

    
    return 0;
}

