/*Implement readv() and writev() using read(), write(), and suitable functions from the
malloc package (Section 7.1.2).
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct my_iovec {
    void *iov_base;
    size_t iov_len; 
};

int my_readv(int fd, struct my_iovec *iov, int iovcnt) {
    int total_bytes_read = 0;
    for (int i = 0; i < iovcnt; i++) {
        int bytes_read = read(fd, iov[i].iov_base, iov[i].iov_len);
        if (bytes_read == -1) return -1;
        total_bytes_read += bytes_read;
        if (bytes_read < iov[i].iov_len) break;
    }
    return total_bytes_read;
}

int my_writev(int fd, struct my_iovec *iov, int iovcnt) {
    int total_bytes_written = 0;
    for (int i = 0; i < iovcnt; i++) {
        int bytes_written = write(fd, iov[i].iov_base, iov[i].iov_len);
        if (bytes_written == -1) return -1;
        total_bytes_written += bytes_written;
        if (bytes_written < iov[i].iov_len) break;
    }
    return total_bytes_written;
}

int main() {
    struct my_iovec iov[2];
    char buf1[6] = "Hello";
    char buf2[6] = "world";
    iov[0].iov_base = buf1;
    iov[0].iov_len = 6;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 6;
    int fd = 1; // stdout
    int bytes_written = my_writev(fd, iov, 2);
    if (bytes_written == -1) {
        printf("Error writing to file descriptor\n");
        return 1;
    }

    int bytes_read = my_readv(fd, iov, 2);
    if (bytes_read == -1) {
        printf("Error reading from file descriptor\n");
        return 1;
    }

    return 0;
}


