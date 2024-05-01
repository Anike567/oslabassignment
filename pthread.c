#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *myfunc(void *vargp){
    int num = 10;
    while(num--) {
        sleep(1);
        printf("Printing Hello world from thread                  ");
    }
    return NULL;
}




int main(void){
    printf("pthread is exist\n");
    pthread_t id;
    pthread_create(&id,NULL,myfunc,NULL);

    int num = 10;
    while(num--){
        sleep(1);
        printf("Printing Hello world from main thread\n");
    }

    pthread_join(id,NULL);
  
    return 0;
}

