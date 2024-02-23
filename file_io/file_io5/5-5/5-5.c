/*Write a program to verify that duplicated file descriptors share a file offset value
and open file status flags.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
   int fd = open("test.txt", O_RDWR | O_CREAT);
   if (fd == -1) {
        printf("error open");
    }

    int fd_dup = dup(fd);
    off_t offset = lseek(fd, 10, SEEK_SET);
    off_t offset_dup = lseek(fd_dup, 0, SEEK_CUR);
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        printf("error fcntl");
    }
    int flags_dup = fcntl(fd_dup, F_GETFL);
    if (flags_dup == -1) {
        printf("error fcntl");
    }
    printf("File offset for fd: %ld\n", (long) offset);
    printf("File offset for fd_dup: %ld\n", (long) offset_dup);
    printf("Flags for fd: %d\n", flags);
    printf("Flags for fd_dup: %d\n", flags_dup);
    close(fd);
    close(fd_dup);

    return 0;
}

