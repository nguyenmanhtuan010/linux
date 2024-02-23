/*
Write a program to demonstrate that different threads in the same process can have
different sets of pending signals, as returned by sigpending(). You can do this by
using pthread_kill() to send different signals to two different threads that have 
blocked these signals, and then have each of the threads call sigpending() and 
display information about pending signals. (You may find the functions in Listing 
20-4 useful.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func1(void *arg) {
	
    pthread_t tid = *(pthread_t *)arg;
	pthread_kill(tid,SIGUSR1);
    sigset_t pending_set;
    sigpending(&pending_set);
    if (sigismember(&pending_set, SIGUSR1)) {
        printf("SIGUSR1 is in the pending set\n");
    } else {
        printf("SIGUSR1 is not in the pending set\n");
    }
}

void *thread_func2(void *arg) {
    pthread_t tid = *(pthread_t *)arg;
	pthread_kill(tid,SIGUSR2);
    sigset_t pending_set;
    sigpending(&pending_set);
    if (sigismember(&pending_set, SIGUSR2)) {
        printf("SIGUSR2 is in the pending set\n");
    } else {
        printf("SIGUSR2 is not in the pending set\n");
    }
}
int main() {
    
    pthread_t tid1, tid2;
    sigset_t mask_set;
    sigemptyset(&mask_set);
    sigaddset(&mask_set, SIGUSR1);
    sigaddset(&mask_set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask_set, NULL);
 
    pthread_create(&tid1, NULL, thread_func1, (void *)&tid1);
    pthread_create(&tid2, NULL, thread_func2, (void *)&tid2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
