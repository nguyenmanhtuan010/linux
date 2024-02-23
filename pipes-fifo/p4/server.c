/*Write programs to verify the operation of nonblocking opens and 
nonblocking I/O on FIFOs (see Section 44.9).*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "fifo_seqnum.h"

#define MAX_BUFFER 256
int main(int argc, char *argv[]) {
    int serverFd;
    char buf[MAX_BUFFER];
    mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP);
    serverFd = open(SERVER_FIFO, O_RDONLY | O_NONBLOCK);
    while(1){
		read(serverFd, buf, MAX_BUFFER);
		printf("Received message from client: %s\n", buf);
		sleep(1);
    }
    printf("Server exiting...\n");
    unlink(SERVER_FIFO);
    exit(EXIT_SUCCESS);
	
}
