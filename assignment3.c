#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

void handle_interrupt(int sig){
    if(sig == SIGTSTP){
        exit(0);
    }
    if(sig == SIGINT){
        int n;
        printf("enter the value of n \n");
        scanf("%d",&n);
        int p[2];
        int flag=pipe(p);
        if(flag < 0){
            perror("error occurs in creating pipe \n");
            exit(0);
        }
        switch(fork()){
            case -1:
                perror("error in creating process\n");
                exit(1);
            case 0:
                int pre=0,curr=1;
                close(p[0]); 
                write(p[1], &pre, sizeof(pre));
                write(p[1], &curr, sizeof(curr));
                while(curr <= n){
                    int temp=pre+curr;
                    write(p[1], &temp, sizeof(temp));
                    pre= curr;
                    curr=temp;
                }
                close(p[1]);
                exit(0);

            default:
                int msg;
                close(p[1]);
                while(read(p[0], &msg, sizeof(msg)) > 0){
                    printf(" %d ",msg);
                }
                close(p[0]); 
        }
    }
}

int main(void){
    signal(SIGINT, handle_interrupt);
    signal(SIGTSTP, handle_interrupt);
    
    while(1){
        printf("Date:   ");
        fflush(stdout);
        system("date +%F");

        printf("Time:   ");
        fflush(stdout); 
        system("date +%T");
        printf("\n");

        sleep(1);
    }

    return 0;
}
