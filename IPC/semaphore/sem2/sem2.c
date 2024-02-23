/*Triển khai các ngữ nghĩa POSIX bằng cách sử dụng các ngữ nghĩa System V.*/

#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

// Tạo một semaphore
int sem_create(key_t key) {
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    return semid;
}

// Mở một semaphore tồn tại
int sem_open_existing(key_t key) {
    int semid = semget(key, 1, 0);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    return semid;
}

// Đặt giá trị semaphore
void sem_set(int semid, int value) {
    union semun arg;
    arg.val = value;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        exit(EXIT_FAILURE);
    }
}

// Hoạt động chờ (P)
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop wait");
        exit(EXIT_FAILURE);
    }
}

// Hoạt động báo hiệu (V)
void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop signal");
        exit(EXIT_FAILURE);
    }
}

// Xóa semaphore
void sem_remove(int semid) {
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(EXIT_FAILURE);
    }
}

int main() {
    key_t key = ftok(".", 's'); // Tạo một key cho semaphore

    // Tạo một semaphore mới
    int semid = sem_create(key);

    // Đặt giá trị ban đầu của semaphore
    sem_set(semid, 1);

    // Thực hiện các hoạt động chờ và báo hiệu
    sem_wait(semid);
    printf("Giá trị của semaphore sau hoạt động chờ: %d\n", semctl(semid, 0, GETVAL));
    sem_signal(semid);
    printf("Giá trị của semaphore sau hoạt động báo hiệu: %d\n", semctl(semid, 0, GETVAL));

    // Xóa semaphore
    sem_remove(semid);

    return 0;
}
