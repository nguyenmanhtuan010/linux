/*Write a program that shows that when the disposition of a pending signal is
changed to be SIG_IGN, the program never sees (catches) the signal.*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Hàm handler cho tín hiệu SIGINT
void sigint_handler(int signal) {
    printf("Caught SIGINT signal\n");
}

int main() {
    // Đặt handler cho tín hiệu SIGINT
    signal(SIGINT, sigint_handler);

    printf("Sending SIGINT signal...\n");

    // Gửi tín hiệu SIGINT
    raise(SIGINT);

    // Thay đổi disposition của SIGINT thành SIG_IGN
    signal(SIGINT, SIG_IGN);

    printf("Sending SIGINT signal again...\n");

    // Gửi tín hiệu SIGINT
    raise(SIGINT);

    printf("Program exiting...\n");

    return 0;
}
