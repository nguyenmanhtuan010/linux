/*As noted in Section 20.3, sigaction() is more portable than signal() for establishing a
signal handler. Replace the use of signal() by sigaction() in the program in Listing 20-7
(sig_receiver.c).*/
#include <signal.h>
#include "signal_functions.h" /* Declaration of printSigset() */
#include "tlpi_hdr.h"
static int sigCnt[NSIG]; /* Counts deliveries of each signal */
static volatile sig_atomic_t gotSigint = 0;
/* Set nonzero if SIGINT is delivered */
static void
handler(int sig)
{
    if (sig == SIGINT)
        gotSigint = 1;
    else
        sigCnt[sig]++;
}
int
main(int argc, char *argv[])
{
    int n, numSecs;
    sigset_t pendingMask, blockingMask, emptyMask;
    struct sigaction sa;

    printf("%s: PID is %ld\n", argv[0], (long) getpid());

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    for (n = 1; n < NSIG; n++) /* Same handler for all signals */
        sigaction(n, &sa, NULL); /* Ignore errors */

    if (argc > 1) {
        numSecs = getInt(argv[1], GN_GT_0, NULL);
        sigfillset(&blockingMask);
        if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
            errExit("sigprocmask");
        printf("%s: sleeping for %d seconds\n", argv[0], numSecs);
        sleep(numSecs);
        if (sigpending(&pendingMask) == -1)
            errExit("sigpending");
        printf("%s: pending signals are: \n", argv[0]);
        printSigset(stdout, "\t\t", &pendingMask);
        sigemptyset(&emptyMask); /* Unblock all signals */
        if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
            errExit("sigprocmask");
    }

    while (!gotSigint) /* Loop until SIGINT caught */
        continue;

    for (n = 1; n < NSIG; n++) /* Display number of signals received */
        if (sigCnt[n] != 0)
            printf("%s: signal %d caught %d time%s\n", argv[0], n,
                   sigCnt[n], (sigCnt[n] == 1) ? "" : "s");

    exit(EXIT_SUCCESS);
}

