#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/dgram_socket4"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    // Receive datagrams
    while (1) {
		sleep(5);
        ssize_t numBytes = recv(sockfd, buffer, BUFFER_SIZE, 0);
        buffer[numBytes] = '\0';
        printf("Received: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);
    unlink(SOCKET_NAME); // SOCKET_NAME là đường dẫn tới tệp socket
    return 0;
}
