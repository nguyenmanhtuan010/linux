/*
Write a program to see how fast the fork() and vfork() system calls are on your
system. Each child process should immediately exit, and the parent should wait()
on each child before creating the next
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define NUM_CHILDREN 1000

int main() {
    pid_t pid;
    int i;
    clock_t start, end;
    double cpu_time_used;

    // Measure time for fork()
    start = clock();
    for (i = 0; i < NUM_CHILDREN; i++) {
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d fork() calls: %f seconds\n", NUM_CHILDREN, cpu_time_used);

    // Measure time for vfork()
    start = clock();
    for (i = 0; i < NUM_CHILDREN; i++) {
        if ((pid = vfork()) < 0) {
            perror("vfork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d vfork() calls: %f seconds\n", NUM_CHILDREN, cpu_time_used);

    return 0;
}

