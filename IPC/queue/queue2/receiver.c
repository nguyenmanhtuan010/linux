#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    mqd_t mqd;
    char msg_buffer[256];
    struct mq_attr attr;
    unsigned int prio;

    mqd = mq_open("/my_queue", O_RDONLY);
    if (mqd == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    if (mq_getattr(mqd, &attr) == -1) {
        perror("mq_getattr");
        exit(1);
    }

    while (1) {
        ssize_t numRead = mq_receive(mqd, msg_buffer, attr.mq_msgsize, &prio);
        if (numRead == -1) {
            perror("mq_receive");
            mq_close(mqd);
            exit(1);
        }

        msg_buffer[numRead] = '\0'; // Add null terminator to make it a valid string
        printf("Received message with priority %u: %s\n", prio, msg_buffer);

        if (strcmp(msg_buffer, "exit") == 0) {
            break;
        }
    }

    // Close the message queue
    mq_close(mqd);

    return 0;
}
