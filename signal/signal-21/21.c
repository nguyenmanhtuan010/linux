/* Implement abort().*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void abort_program() {
	
    fprintf(stderr, "abort()\n");
    raise(SIGABRT);
    fprintf(stderr, "abort() didn't terminate\n");
    exit(EXIT_FAILURE);
}

int main() {
    
    signal(SIGABRT, SIG_DFL);
    abort_program();

    return 0;
}

