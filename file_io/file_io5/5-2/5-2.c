/*Write a program that opens an existing file for writing with the O_APPEND flag, and
then seeks to the beginning of the file before writing some data. Where does the
data appear in the file? Why?
 Khi ghi dữ liệu vào tệp, dữ liệu sẽ vẫn được ghi vào cuối tệp, bất kể chúng ta đã chuyển con trỏ tệp đến đâu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main() {
    char *file_path = "test.txt";
    int fd = open(file_path, O_WRONLY| O_CREAT | O_APPEND);

    if (fd == -1) {
        printf("error");
    }
    lseek(fd, 0, SEEK_SET);
    char *data = "Hello, world!\n";
    write(fd, data, strlen(data));
    close(fd);
    return 0;
}

