/*Write a program to show that if the evp argument to timer_create() is specified as
NULL, then this is equivalent to specifying evp as a pointer to a sigevent structure with
sigev_notify set to SIGEV_SIGNAL, sigev_signo set to SIGALRM, and si_value.sival_int set to
the timer ID.*/
#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void timer_handler(int sig, siginfo_t *si, void *uc) {
    printf("Timer expired\n");
}

int main() {
    struct sigevent sev;
    timer_t timerid;
    struct itimerspec its;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    // Create the timer
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_int = 12345; // Timer ID
    timer_create(CLOCK_REALTIME, NULL, &timerid);

    its.it_value.tv_sec = 2;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &its, NULL);

    sleep(3);

    return 0;
}
