/*Sửa đổi chương trình trong Liệt kê 53-3 (psem_wait.c) để sử dụng sem_timedwait()
thay vì sem_wait(). Chương trình sẽ nhận thêm một đối số dòng lệnh chỉ định số giây 
(tương đối) được sử dụng làm thời gian chờ cho cuộc gọi sem_timedwait()*/

#include <semaphore.h>
#include "tlpi_hdr.h"
#include <time.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    sem_t *sem;
    int timeout;
    struct timespec ts;
	
    sem = sem_open("/my_sem", O_CREAT, 0666);
    if (sem == SEM_FAILED) {
        errExit("sem_open");
    }

    timeout = atoi(argv[2]);
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout;

    if (sem_timedwait(sem, &ts) == -1) {
        if (errno == ETIMEDOUT) {
            printf("sem_timedwait() timed out\n");
        } else {
            errExit("sem_timedwait");
        }
    } else {
        printf("%ld sem_timedwait() succeeded\n", (long)getpid());
    }

    exit(EXIT_SUCCESS);
}

