/*Write a simple chat program (similar to talk(1), but without the curses interface)
using POSIX messages queues.*/

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    mqd_t mqd;
    char msg_buffer[256];

    mqd = mq_open("/my_queue", O_CREAT | O_WRONLY, 0666, NULL);

    while (1) {
        printf("Enter message: ");
        fgets(msg_buffer, sizeof(msg_buffer), stdin);
        msg_buffer[strcspn(msg_buffer, "\n")] = '\0';
        if (strcmp(msg_buffer, "exit") == 0) {
            break;
        }
        if (mq_send(mqd, msg_buffer, strlen(msg_buffer), 0) == -1) {
            perror("mq_send");
            mq_close(mqd);
            exit(1);
        }
    }
    // Close the message queue
    mq_close(mqd);

    return 0;
}

