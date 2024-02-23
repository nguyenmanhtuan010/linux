/*Listing 26-4 (make_zombie.c) uses a call to sleep() to allow the child process a chance
to execute and terminate before the parent executes system(). This approach
produces a theoretical race condition. Modify the program to eliminate the race
condition by using signals to synchronize the parent and child.*/
#include <signal.h>
#include <libgen.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200

static void
handler(int sig)
{
    /* Handler for signal sent by child when it terminates */

    /* Nothing to do, just return to wake up the parent */
}

int main(int argc, char *argv[])
{
    char cmd[CMD_SIZE];
    pid_t childPid;

    setbuf(stdout, NULL); /* Disable buffering of stdout */
    printf("Parent PID=%ld\n", (long)getpid());

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
        errExit("sigaction");

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");
    case 0: /* Child: immediately exits to become zombie */
        printf("Child (PID=%ld) exiting\n", (long)getpid());
        _exit(EXIT_SUCCESS);
    default: /* Parent */
        /* Wait for child to terminate */
        pause();
        snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
        cmd[CMD_SIZE - 1] = '\0'; /* Ensure string is null-terminated */
        system(cmd);               /* View zombie child */

        /* Now send the "sure kill" signal to the zombie */
        if (kill(childPid, SIGKILL) == -1)
            errMsg("kill");

        sleep(3); /* Give child a chance to react to signal */
        printf("After sending SIGKILL to zombie (PID=%ld):\n", (long)childPid);
        system(cmd); /* View zombie child again */
        exit(EXIT_SUCCESS);
    }
}
