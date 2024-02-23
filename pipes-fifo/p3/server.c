/*The server in Listing 44-7 (fifo_seqnum_server.c) always starts assigning sequence
numbers from 0 each time it is started. Modify the program to use a backup file
that is updated each time a sequence number is assigned. (The open() O_SYNC flag,
described in Section 4.3.1, may be useful.) At startup, the program should check
for the existence of this file, and if it is present, use the value it contains to initialize
the sequence number. If the backup file can’t be found on startup, the program
should create a new file and start assigning sequence numbers beginning at 0. (An
alternative to this technique would be to use memory-mapped files, described in
Chapter 49.)*/
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "fifo_seqnum.h"

#define BACKUP_FILE "seqnum_backup.txt"

int main(int argc, char *argv[])
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;

    int backupFd = open(BACKUP_FILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    read(backupFd, &seqNum, sizeof(int));

    umask(0);
    mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP);
    serverFd = open(SERVER_FIFO, O_RDONLY);
    dummyFd = open(SERVER_FIFO, O_WRONLY);
    signal(SIGPIPE, SIG_IGN);

    for (;;)
    {
        read(serverFd, &req, sizeof(struct request));
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long)req.pid);
        clientFd = open(clientFifo, O_WRONLY);
        resp.seqNum = seqNum;
        write(clientFd, &resp, sizeof(struct response));
        close(clientFd);
		
        seqNum += req.seqLen;
        lseek(backupFd, 0, SEEK_SET);
        write(backupFd, &seqNum, sizeof(int));
    }
}
