#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>   

extern int errno;
void read_file(){
    int fd=open("unit2.txt",O_RDWR | O_CREAT,0644);
    if(fd == -1){
        printf("error no %d\n",errno);
    }
    else{
        struct flock lock;
        if(fcntl(fd,F_GETLK,&lock) == -1){
            printf("error in getting lock\n");
        }
        else{
            if(lock.l_type == F_UNLCK){
                lock.l_type= F_WRLCK;
                lock.l_whence=SEEK_SET;
                lock.l_start=0;
                lock.l_len=0;
                lock.l_pid=getpid();    
                if(fcntl(fd,F_SETLK,&lock) == -1){
                    printf("error occurs in setting lock to file\n");
                }
                else{
                    printf("lock set successfully\n");
                }

                int n=10;
                while(n--){
                    sleep(2);
                }
                
            }
            else{
                printf("file is locked by process %d\n",lock.l_pid);
            }
        }

    }

    int val= close(fd);
    if(val == 0){
        printf("File closed successfully\n");
    }
    else{
        printf("error occured in closing this file\n");
    }

}

int main(void){
    read_file();
    return 0;
}