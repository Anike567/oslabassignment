#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
void ctrl_c(int sig){
    if(sig == 20){
        exit(0);
    }
    else{
        printf("Bhaag Bhsdk\n");
    }
    sleep(1);
}
int main(void){
    signal(SIGTSTP,ctrl_c);
    signal(SIGINT,ctrl_c);
    while (1)
    {
        printf("Process is running\n");
        sleep(1);
    }
    
    return 0;
}
