/*Replace the use of waitpid() with waitid() in Listing 26-3 (child_status.c). The call to
printWaitStatus() will need to be replaced by code that prints relevant fields from
the siginfo_t structure returned by waitid().*/

#include <sys/wait.h>
#include "tlpi_hdr.h"
#include "get_num.h"
#include "error_functions.h"

int main(int argc, char *argv[]) {
    int status;
    pid_t childPid;
    siginfo_t siginfo;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [exit-status]\n", argv[0]);

    switch (fork()) {
        case -1:
            errExit("fork");
        case 0:
            exit(EXIT_FAILURE); 
        default:
            for (;;) {
                if (waitid(P_ALL, 0, &siginfo, WEXITED | WSTOPPED | WCONTINUED) == -1)
                    errExit("waitid");

                childPid = siginfo.si_pid;
                status = siginfo.si_status;

                printf("waitid() returned: PID=%ld; status=0x%04x (%d,%d)\n", (long)childPid, 
				(unsigned int)status, status >> 8, status & 0xff);
                printf("siginfo.si_pid: %ld\n", (long)siginfo.si_pid);
                printf("siginfo.si_status: %d\n", siginfo.si_status);
                printf("siginfo.si_code: %d\n", siginfo.si_code);

                if (WIFEXITED(status) || WIFSIGNALED(status))
                    exit(EXIT_SUCCESS);
            }
    }

    return 0;
}
