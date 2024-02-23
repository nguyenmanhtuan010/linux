/*Modify the program in Listing 52-5 (pmsg_receive.c) to accept a timeout (a relative
number of seconds) on the command line, and use mq_timedreceive() instead of
mq_receive().*/

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256

int main() {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    char buffer[MAX_MSG_SIZE];
    unsigned int prio;
    struct timespec abs_timeout;
    clock_gettime(CLOCK_REALTIME, &abs_timeout);
    abs_timeout.tv_sec += 5; // Timeout of 5 seconds

    ssize_t numRead = mq_timedreceive(mq, buffer, MAX_MSG_SIZE, &prio, &abs_timeout);
    if (numRead == -1) {
        if (errno == ETIMEDOUT) {
            printf("Timed out. No message received.\n");
        } else {
            perror("mq_timedreceive");
        }
    } 
	else {
        buffer[numRead] = '\0'; // Null-terminate the received message
        printf("Received message: %s\n", buffer);
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
