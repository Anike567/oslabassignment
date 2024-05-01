#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

FILE *fp;
volatile sig_atomic_t signal_received = 0; // Flag to indicate signal received

void signalhandler(int);

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } 
    if (pid == 0) {
        // Child process
        fp = fopen("a.txt", "a+");
        if (fp == NULL) {
            perror("failed to open file");
            exit(EXIT_FAILURE);
        }

        // Register signal handler for SIGINT (Ctrl+C)
        signal(SIGINT, signalhandler);

        // Child process waits for signals passively
        while (!signal_received) {
            sleep(1); // Sleep to avoid consuming CPU
        }

        // Write message to file if signal received
        fputs("Ctrl+C interrupt occurred\n", fp);
        fflush(fp); // Flush buffer to ensure the message is written immediately
        fclose(fp); // Close file
        exit(EXIT_SUCCESS);
    }
    else {
        // Parent process
        printf("Daemon process started with PID: %d\n", pid);
        printf("Parent process exited\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}

void signalhandler(int signal) {
    if (signal == SIGINT) {
        signal_received = 1; // Set flag to indicate signal received
    }
}
