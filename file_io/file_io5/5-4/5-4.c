/*Implement dup() and dup2() using fcntl() and, where necessary, close(). (You may
ignore the fact that dup2() and fcntl() return different errno values for some error
cases.) For dup2(), remember to handle the special case where oldfd equals newfd. In
this case, you should check whether oldfd is valid, which can be done by, for example,
checking if fcntl(oldfd, F_GETFL) succeeds. If oldfd is not valid, then the function
should return –1 with errno set to EBADF.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int my_dup(int oldfd) {
    int newfd = fcntl(oldfd, F_DUPFD, 0);
    if (newfd == -1) {
        return -1; 
    }
    return newfd; 
}

int my_dup2(int oldfd, int newfd) {
    if (oldfd == newfd) {
        if (fcntl(oldfd, F_GETFL) == -1) {
            errno = EBADF;
            return -1; 
        }
        return newfd; 
    }

    if (fcntl(newfd, F_GETFL) != -1) {
        close(newfd);
    }

    int result = fcntl(oldfd, F_DUPFD, newfd);
    if (result == -1) {
        return -1; 
    }
    return newfd; 
}

int main() {
    int fd = open("test.txt", O_CREAT | O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int newfd1 = my_dup(fd);
    if (newfd1 == -1) {
        perror("my_dup");
        return 1;
    }

    int newfd2 = my_dup2(fd, 100);
    if (newfd2 == -1) {
        perror("my_dup2");
        return 1;
    }

    printf("Original fd: %d\n", fd);
    printf("New fd (my_dup): %d\n", newfd1);
    printf("New fd (my_dup2): %d\n", newfd2);

    close(fd);
    close(newfd1);
    close(newfd2);

    return 0;
}

