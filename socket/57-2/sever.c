/*Reimplement the sequence-number server and client of Section 44.8 using UNIX
domain stream sockets.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_NAME "/tmp/stream_server_socket1"
#define BUFFER_SIZE 1024

int main() {
    int sockfd, newsockfd;
    struct sockaddr_un addr;
    socklen_t addrlen = sizeof(struct sockaddr_un);
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    listen(sockfd, 5);
    newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addrlen);
    while (1) {
        ssize_t numBytes = recv(newsockfd, buffer, BUFFER_SIZE - 1, 0);
			if (numBytes == 0) {
            printf("Client closed connection\n");
            break;
        }
        buffer[numBytes] = '\0';
        printf("Received: %s\n", buffer);
    }

    close(newsockfd);
    close(sockfd);
    unlink(SOCKET_NAME);

    return 0;
}
