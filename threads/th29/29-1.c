/* What possible outcomes might there be if a thread executes the following code:
pthread_join(pthread_self(), NULL);
Write a program to see what actually happens on Linux. If we have a variable, tid,
containing a thread ID, how can a thread prevent itself from making a call,
pthread_join(tid, NULL), that is equivalent to the above statement?*/
#include <pthread.h>
#include <stdio.h>

void *thread_func(void *arg) {
    pthread_t tid = *(pthread_t *)arg;
    if (pthread_equal(pthread_self(), tid)) {
        printf("Thread is attempting to join itself.\n");
    } else {
        pthread_join(tid, NULL);
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, (void *)&tid);
    pthread_join(tid, NULL);
    return 0;
}

