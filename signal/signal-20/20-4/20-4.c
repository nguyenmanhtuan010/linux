/*Implement siginterrupt() using sigaction()*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int siginterrupt(int sig, int flag) {
    struct sigaction sa;
    if (sigaction(sig, NULL, &sa) == -1) {
        perror("sigaction");
        return -1;
    }

    if (flag) {
        sa.sa_flags &= ~SA_RESTART;
    } else {
        sa.sa_flags |= SA_RESTART;
    }

    if (sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction");
        return -1;
    }

    return 0;
}

void sigint_handler(int signal) {
    printf("Caught SIGINT signal\n");
}

int main() {

    signal(SIGINT, sigint_handler);
    printf("Sending SIGINT signal...\n");
    raise(SIGINT); 
    siginterrupt(SIGINT, 1);
    printf("Sending SIGINT signal again...\n");
    raise(SIGINT);
    printf("Program exiting...\n");

    return 0;
}
