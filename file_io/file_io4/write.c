/*The tee command reads its standard input until end-of-file, writing a copy of the input
to standard output and to the file named in its command-line argument. (We show
an example of the use of this command when we discuss FIFOs in Section 44.7.)
Implement tee using I/O system calls. By default, tee overwrites any existing file with
the given name. Implement the –a command-line option (tee –a file), which causes tee
to append text to the end of a file if it already exists. (Refer to Appendix B for a
description of the getopt() function, which can be used to parse command-line
options.)
./4-1 output.txt
./4-1 -a output.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int append = 0;
    int opt;
    opt = getopt(argc, argv, "a");
    if(opt == 'a') {
        append = 1;
    }
    char *filename = argv[optind];
    int fd;
    if (append) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    } else {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;
    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
        write(fd, buffer, bytesRead);
    }
    close(fd);
    return 0;
}

