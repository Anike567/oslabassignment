#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void thread_function(void *args) {
    printf("Hello World\n"); 
}

int main(void) {
    pthread_t threadid;
    pthread_create(&threadid, NULL, thread_function, NULL);
    pthread_join(threadid, NULL);

    return 0;
}
