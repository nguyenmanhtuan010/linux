/*Modify the program in Listing 30-1 (thread_incr.c) so that each loop in the 
thread’s start function outputs the current value of glob and some identifier 
that uniquely identifies the thread. The unique identifier for the thread could 
be specified as an argument to the pthread_create() call used to create the 
thread. For this program, that would require changing the argument of the thread’s
start function to be a pointer to a structure containing the unique identifier 
and a loop limit value. Run the program, redirecting output to a file, and then 
inspect the file to see what happens to glob as the kernel scheduler alternates 
execution between the two threads.
.*/
#include <pthread.h>
#include "tlpi_hdr.h"

static int glob = 0;
static void *threadFunc(void *arg)
{
    pthread_t tid = *(pthread_t *)arg;
    int loc, j;
    for (j = 0; j < 100; j++) {
        loc = glob;
        loc++;
        glob = loc;
        printf("Thread %ld: glob = %d\n", tid, glob);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    freopen("output.txt", "w", stdout);
	
    pthread_create(&t1, NULL, threadFunc, &t1);
    pthread_create(&t2, NULL, threadFunc, &t2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("glob = %d\n", glob);

    exit(EXIT_SUCCESS);
}

