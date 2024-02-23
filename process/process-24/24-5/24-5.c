/*Suppose that in the program in Listing 24-6, the child process also needed to wait
on the parent to complete some actions. What changes to the program would be
required in order to enforce this*/
#include <signal.h>
#include "curr_time.h" /* Declaration of currTime() */
#include "tlpi_hdr.h"
char *currTime(const char *fmt);

#define SYNC_SIG_PARENT SIGUSR1 /* Synchronization signal for parent */
#define SYNC_SIG_CHILD SIGUSR2  /* Synchronization signal for child */

static void /* Signal handler for parent process */
handler_parent(int sig)
{
    /* Does nothing but return */
}

static void /* Signal handler for child process */
handler_child(int sig)
{
    /* Does nothing but return */
}

int main(int argc, char *argv[])
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout, NULL); /* Disable buffering of stdout */

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SYNC_SIG_PARENT);
    sigaddset(&blockMask, SYNC_SIG_CHILD);

    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
        errExit("sigprocmask");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    /* Install signal handlers for parent and child */
    sa.sa_handler = handler_parent;
    if (sigaction(SYNC_SIG_PARENT, &sa, NULL) == -1)
        errExit("sigaction");

    sa.sa_handler = handler_child;
    if (sigaction(SYNC_SIG_CHILD, &sa, NULL) == -1)
        errExit("sigaction");

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");
    case 0: /* Child */
        /* Child does some required action here... */
        printf("[%s %ld] Child started - doing some work\n",
               currTime("%T"), (long)getpid());
        sleep(2); /* Simulate time spent doing some work */
        /* And then signals parent that it's done */
        printf("[%s %ld] Child about to signal parent\n",
               currTime("%T"), (long)getpid());
        if (kill(getppid(), SYNC_SIG_PARENT) == -1)
            errExit("kill");
        /* Child waits for signal from parent */
        sigemptyset(&emptyMask);
        if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
            errExit("sigsuspend");
        printf("[%s %ld] Child got signal from parent\n",
               currTime("%T"), (long)getpid());
        /* Now child can do other things... */
        _exit(EXIT_SUCCESS);

    default: /* Parent */
        /* Parent may do some work here, and then waits for child to
           complete the required action */
        printf("[%s %ld] Parent about to wait for signal\n",
               currTime("%T"), (long)getpid());
        sigemptyset(&emptyMask);
        if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
            errExit("sigsuspend");
        printf("[%s %ld] Parent got signal from child\n",
               currTime("%T"), (long)getpid());
        if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
            errExit("sigprocmask");
        exit(EXIT_SUCCESS);
    }
}
