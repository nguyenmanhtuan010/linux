/*Suppose that we have three processes related as grandparent, parent, and child,
and that the grandparent doesn’t immediately perform a wait() after the parent
exits, so that the parent becomes a zombie. When do you expect the grandchild to
be adopted by init (so that getppid() in the grandchild returns 1): after the parent
terminates or after the grandparent does a wait()? Write a program to verify your
answer*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
 
    pid_t child_pid, parent_pid, grand_pid;
    grand_pid = fork();
    if (grand_pid == 0) {
        parent_pid = fork();
           if (parent_pid == 0) {
            printf("child: My PID is %d, my parent's PID is %d\n", getpid(), getppid());
            sleep(2); // Wait for a while
            printf("child: My parent's PID is now %d\n", getppid());
        } else {
            printf("parent: My PID is %d, my parent's PID is %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    } 
	else {
        printf("grand: My PID is %d\n", getpid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}

