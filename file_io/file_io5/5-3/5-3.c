/*This exercise is designed to demonstrate why the atomicity guaranteed by opening
a file with the O_APPEND flag is necessary. Write a program that takes up to three
command-line arguments:
            $ atomic_append filename num-bytes [x]
This file should open the specified filename (creating it if necessary) and append
num-bytes bytes to the file by using write() to write a byte at a time. By default, the
program should open the file with the O_APPEND flag, but if a third command-line
argument (x) is supplied, then the O_APPEND flag should be omitted, and instead the
program should perform an lseek(fd, 0, SEEK_END) call before each write(). Run
two instances of this program at the same time without the x argument to write
1 million bytes to the same file:
            $ atomic_append f1 1000000 & atomic_append f1 1000000
Repeat the same steps, writing to a different file, but this time specifying the x
argument:
            $ atomic_append f2 1000000 x & atomic_append f2 1000000 x
List the sizes of the files f1 and f2 using ls –l and explain the difference

	Khi chạy hai phiên bản mà không có đối số x, cả hai đều sử dụng cờ O_APPEND, dẫn
đến việc các ghi vào tệp xảy ra một cách nguyên tử. Do đó, kích thước của tệp f1 sẽ là 
chính xác 2 triệu byte và không có dữ liệu bị mất.
	Khi chạy hai phiên bản với đối số x, cả hai đều sử dụng lseek(fd, 0, SEEK_END) trước
mỗi lần ghi, không đảm bảo tính nguyên tử của các ghi. Kết quả là, tệp f2 có thể có kích 
thước nhỏ hơn 2 triệu byte và dữ liệu có thể bị ghi đè
	Vì vậy, sau khi chạy, tệp f1 sẽ có kích thước chính xác là 2 triệu byte, trong khi tệp
f2 có thể có kích thước nhỏ hơn và dữ liệu có thể bị ghi đè.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    int use_lseek = (argc == 4 && strcmp(argv[3], "x") == 0);

    int fd = open(filename, O_WRONLY | O_CREAT);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_bytes; i++) {
        if (use_lseek) {
            lseek(fd, 0, SEEK_END);
        }

        write(fd, "a", 1);
    }
    close(fd);
    return 0;
}

