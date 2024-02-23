/*Write programs that verify the effect of the SA_RESETHAND flags when
establishing a signal handler with sigaction().*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signal) {
    printf("Caught SIGINT signal\n");
}

int main() {
	
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &sa, NULL);
    printf("Sending SIGINT signal...\n");
    raise(SIGINT);
    printf("Sending SIGINT signal again...\n");
    raise(SIGINT);
    printf("Program exiting...\n");

    return 0;
}
