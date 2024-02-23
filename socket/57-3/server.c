/*Rewrite the programs in Listing 57-3 (us_xfr_sv.c) and Listing 57-4 (us_xfr_cl.c) to
use the Linux-specific abstract socket namespace (Section 57.6).*/

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SOCK_PATH "mysocket"

int main() {
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[100];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path + 1, SOCK_PATH, sizeof(addr.sun_path) - 2);

    bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    listen(sfd, 5);

    for (;;) {
        cfd = accept(sfd, NULL, NULL);
        while ((numRead = read(cfd, buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, numRead);
        }
        close(cfd);
    }

    return 0;
}
