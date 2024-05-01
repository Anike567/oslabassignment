#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>
#include<stdlib.h>

void createchil_process(){
   
}
void handle_sigint(int sig) {
    pid_t pid=fork();
    if(pid == -1){
        perror("Internal error for creating fork\n");
    }
    else if( pid == 0){
       printf( "\nChild id    %d\n",getpid());


    }
    else{
        printf("\nParent id   %d\n",getpid());
    }

    exit(0);
}

int main() 
{ 
    signal(SIGINT, handle_sigint); 
    
    while (1) 
    { 
        printf("Process is running \n"); 
        sleep(1); 
    } 
    return 0; 
} 
