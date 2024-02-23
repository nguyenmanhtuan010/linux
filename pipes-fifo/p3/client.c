#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "fifo_seqnum.h"

int main(int argc, char *argv[])
{
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long)getpid());
    mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP);
    int serverFd = open(SERVER_FIFO, O_WRONLY);
    req.pid = getpid();
    req.seqLen = atoi(argv[1]);
    write(serverFd, &req, sizeof(struct request));
    int clientFd = open(clientFifo, O_RDONLY);
    read(clientFd, &resp, sizeof(struct response));
    printf("Client %ld: Received sequence number %d\n", (long)getpid(), resp.seqNum);
    close(clientFd);
    unlink(clientFifo);
    exit(EXIT_SUCCESS);
}
