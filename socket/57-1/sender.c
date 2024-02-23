/*
Reimplement the sequence-number server and client using UNIX
domain datagrams sockets
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

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
    int i = 0;
    while(1){
        sprintf(buffer, "Message %d", ++i);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
        printf("Sent: %s\n", buffer);
		sleep(1);
    }

    close(sockfd);
    unlink(SOCKET_NAME); 

    return 0;
}
