/*Write a program to demonstrate that after a vfork(), the child process can close a
file descriptor (e.g., descriptor 0) without affecting the corresponding file descriptor
in the parent.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <fcntl.h>

int main() {
    int fd;
    pid_t pid;
    fd = open("hello.txt", O_CREAT | O_RDWR);
    pid = vfork();
	if (pid == 0){ 
        printf("Child process: Closing file descriptor 0\n");
        close(fd);
        _exit(EXIT_SUCCESS);
    } else { // Tiến trình cha
        printf("Parent process: Waiting for child to finish\n");
        wait(NULL);
        printf("Parent process: Child has finished\n");
	    write(fd, "Hello world\n", 17);
    }

    return 0;
}
