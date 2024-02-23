/*Write a program that uses two pipes to enable bidirectional communication
between a parent and child process. The parent process should loop reading a
block of text from standard input and use one of the pipes to send the text 
to the child, which converts it to uppercase and sends it back to the parent 
via the other pipe. The parent reads the data coming back from the child and 
echoes it on standard output before continuing around the loop once more.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
	
    int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];
    char buffer[BUFFER_SIZE];
    pipe(pipe_parent_to_child);
	pipe(pipe_child_to_parent);
    pid_t pid = fork();

    if (pid > 0) { 
        close(pipe_parent_to_child[0]); 
        close(pipe_child_to_parent[1]); 

        while (1) {
            printf("Nhập một chuỗi: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            write(pipe_parent_to_child[1], buffer, BUFFER_SIZE);

            if (strcmp(buffer, "exit\n") == 0) {
                break;
            }

            read(pipe_child_to_parent[0], buffer, BUFFER_SIZE);
            printf("Chuỗi chữ in hoa nhận được từ con: %s\n", buffer);
        }

        close(pipe_parent_to_child[1]); 
        close(pipe_child_to_parent[0]); 
        wait(NULL); 
    } 
	else {
        close(pipe_parent_to_child[1]);
        close(pipe_child_to_parent[0]);

        while (1) {
            read(pipe_parent_to_child[0], buffer, BUFFER_SIZE);
            if (strcmp(buffer, "exit\n") == 0) {
                break;
            }

            for (int i = 0; buffer[i]; i++) {
                buffer[i] = toupper(buffer[i]);
            }

            write(pipe_child_to_parent[1], buffer, BUFFER_SIZE);
        }

        close(pipe_parent_to_child[0]); 
        close(pipe_child_to_parent[1]);
    }

    return 0;
}
