/*dùng shared memory viết chương trình writer.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok(".", 's'); // Tạo key
    int shmid;
    char *shmaddr;

    // Tạo shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Ghi dữ liệu vào shared memory
    strcpy(shmaddr, "Hello from write.c");

    // In thông điệp đã ghi
    printf("Data written to shared memory: %s\n", shmaddr);

    // Detach shared memory segment
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
