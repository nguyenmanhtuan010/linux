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
    serverFd = open(SERVER_FIFO, O_WRONLY | O_NONBLOCK);
    strcpy(buf, "Hello, server!");
	while(1){
		write(serverFd, buf, strlen(buf));
		printf("Sent message to server: %s\n", buf);
		sleep(1);
	}
    close(serverFd);

    exit(EXIT_SUCCESS);
}
