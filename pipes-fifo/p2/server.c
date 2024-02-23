/*Add code to the server in Listing 44-7 (fifo_seqnum_server.c) so that if 
the program receives the SIGINT or SIGTERM signals, it removes the server 
FIFO and terminates.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include "fifo_seqnum.h"

#define SERVER_FIFO "/tmp/seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"

int gotSignal = 0;

void sigHandler(int sig) {
    gotSignal = sig;
}

int main(int argc, char *argv[]) {
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;

   
    umask(0);
    mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP);
    serverFd = open(SERVER_FIFO, O_RDONLY);
    dummyFd = open(SERVER_FIFO, O_WRONLY);


    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
	
    for (;;) {
        read(serverFd, &req, sizeof(struct request));
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long) req.pid);
        clientFd = open(clientFifo, O_WRONLY);
        resp.seqNum = seqNum;
        write(clientFd, &resp, sizeof(struct response));
        close(clientFd);

        seqNum += req.seqLen;
        
        if (gotSignal) {
            unlink(SERVER_FIFO);
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_SUCCESS);
}
