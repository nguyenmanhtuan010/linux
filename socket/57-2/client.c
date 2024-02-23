#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_NAME "/tmp/stream_server_socket1"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];
    int sequenceNumber = 0;
  
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

	while (1) {
		sprintf(buffer, "%d", sequenceNumber++);
		send(sockfd, buffer, strlen(buffer), 0);
		printf("Sent: %s\n", buffer);
		sleep(1); 
	}

    close(sockfd);
    unlink(SOCKET_NAME);
	
    return 0;
}
