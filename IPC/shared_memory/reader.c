/*dùng shared memory viết chương trình reader.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok(".", 's'); // Tạo key
    int shmid;
    char *shmaddr;

    // Lấy shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Đọc dữ liệu từ shared memory
    printf("Data read from shared memory: %s\n", shmaddr);

    // Detach shared memory segment
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
