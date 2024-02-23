/*Write a program to verify that when a child’s parent terminates, 
a call to getppid() returns 1 (the process ID of init).*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	
    pid_t child_pid = fork();
 
    if (child_pid == 0) {
        printf("Child process (PID=%d) is running.\n", getppid());
		sleep(2);
        printf("Child process (PID=%d) is running.\n", getppid());
    } else {
        // Parent process
        printf("Parent process (PID=%d) is running.\n", getpid());
        printf("Parent process is terminating.\n");
        exit(EXIT_SUCCESS); // Exit the parent process
    }

    return 0;
}
