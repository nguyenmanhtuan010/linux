#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SOCK_PATH "mysocket"

int main() {
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[100];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path + 1, SOCK_PATH, sizeof(addr.sun_path) - 2);

    connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    while ((numRead = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        write(sfd, buf, numRead);
    }
    return 0;
}
