#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define _FILE_OFFSET_BITS 64

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }
    int fd = open(argv[1], O_WRONLY);
    if (fd != -1) {
        printf("[PID %ld] Tệp \"%s\" đã tồn tại\n",
               (long) getpid(), argv[1]);
        close(fd);
    } else {
        if (errno != ENOENT) {
            perror("open");
            exit(EXIT_FAILURE);
        } else {
            fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            printf("[PID %ld] Tạo tệp \"%s\" độc quyền\n",
                   (long) getpid(), argv[1]);
        }
    }
    off_t offset = lseek(fd, 0, SEEK_END);
    const char *data = "hello world\n";
    write(fd, data, strlen(data));
    close(fd);
    return 0;
}

