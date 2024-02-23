#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_OPERATIONS 1

int main() {
    int semid;
    struct sembuf sb;
    struct timeval start, end;
    double elapsed;

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);

    gettimeofday(&start, NULL);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        sb.sem_num = 0;
        sb.sem_op = -1;
        sb.sem_flg = 0;
        semop(semid, &sb, 1);

        sb.sem_op = 1;
        semop(semid, &sb, 1);
    }
    gettimeofday(&end, NULL);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Semaphore System V: %f giây\n", elapsed);

    semctl(semid, 0, IPC_RMID);

    return 0;
}
