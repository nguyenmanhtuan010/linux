
/*Implement a function, one_time_init(control, init), that performs the 
equivalent of pthread_once(). The control argument should be a pointer to 
a statically allocated structure containing a Boolean variable and a mutex. 
The Boolean variable indicates whether the function init has already been 
called, and the mutex controls access to that variable. To keep the 
implementation simple, you can ignore possibilities such as init() failing 
or being canceled when first called from a thread(i.e., it is not necessary 
to devise a scheme whereby, if such an event occurs, the next thread that 
calls one_time_init() reattempts the call to init()).*/

#include <stdio.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    int initialized;
} one_time_control;

void one_time_init(one_time_control *control, void (*init)()) {
    pthread_mutex_lock(&control->mutex);
    if (!control->initialized) {
        init();
        control->initialized = 1;
    }
    pthread_mutex_unlock(&control->mutex);
}

void my_init() {
    printf("Initialization done!\n");
}

int main() {
    one_time_control control = {PTHREAD_MUTEX_INITIALIZER, 0};

    one_time_init(&control, my_init);
    one_time_init(&control, my_init);

    return 0;
}
