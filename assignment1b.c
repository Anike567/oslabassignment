#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<utmp.h>

int main(void) {
	pid_t pid;
	struct utmp* utmp_entry;
	switch(pid = fork()) {
	case -1:
		perror("child"); 
		exit(1); 
	case 0:
		printf("Child...\n");
		setutent();
		while((utmp_entry = getutent()) != NULL) {
			if(utmp_entry->ut_type == USER_PROCESS) {
				printf("\tUser: %s\t Terminal: %s\t Host: %s\n", utmp_entry->ut_user, utmp_entry->ut_line, utmp_entry->ut_host);
			}
		}
		endutent();
		printf("\n");
		exit(0);

	default:
		wait(NULL);
		printf("\n");
		printf("Parent: This is the parent process!\n");
		printf("Parent: My PID is %d\n", getpid());
		printf("Parent: My child's PID is %d\n", pid);

	}
	return 0;
}