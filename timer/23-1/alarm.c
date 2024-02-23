/*Although alarm() is implemented as a system call within the Linux kernel, 
this is redundant. Implement alarm() using setitimer().*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void alarm_handler(int signum) {
    printf("Alarm!\n");
}

unsigned int alarm(unsigned int seconds) {
    struct itimerval timer;
    struct sigaction sa;

    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = seconds;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    return 0;  
}

int main() {
    printf("Setting alarm for 3 seconds...\n");
    alarm(3);


    return 0;
}

