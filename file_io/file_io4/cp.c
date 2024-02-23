/*Write a program like cp that, when used to copy a regular file that contains holes
(sequences of null bytes), also creates corresponding holes in the target file.
./4-2 source.txt destination.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {

    char *source_file = argv[1];
    char *destination_file = argv[2];

    int src_fd = open(source_file, O_RDONLY);
    if (src_fd == -1) {
        perror("open source file");
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(destination_file, O_WRONLY);
    if (dest_fd == -1) {
        perror("open destination file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        off_t offset = 0;
        int bytesWritten;
        while (offset < bytesRead) {
            if (buffer[offset] == '\0') {
                off_t holeSize = 1;
                while (offset + holeSize < bytesRead && buffer[offset + holeSize] == '\0') {
                    holeSize++;
                }
                lseek(dest_fd, holeSize, SEEK_CUR);
                offset += holeSize;
            } else {
                bytesWritten = write(dest_fd, buffer + offset, bytesRead - offset);
                offset += bytesWritten;
            }
        }
    }
    close(src_fd);
    close(dest_fd);
	
    return 0;
}