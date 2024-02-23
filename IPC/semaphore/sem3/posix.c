/*POSIX hoạt động tốt hơn nhiều so systemV trong trường hợp semaphore không được kiểm soát. 
Viết hai chương trình để xác minh điều này. Mỗi chương trình nên chỉ cần tăng và giảm một semaphore một số 
lần nhất định. So sánh thời gian cần thiết cho hai chương trình.*/
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_OPERATIONS 1

int main() {
    sem_t semaphore;
    struct timeval start, end;
    double elapsed;

    sem_init(&semaphore, 0, 1);

    gettimeofday(&start, NULL);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        sem_wait(&semaphore);
        sem_post(&semaphore);
    }
    gettimeofday(&end, NULL);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Semaphore POSIX: %f giây\n", elapsed);

    sem_destroy(&semaphore);

    return 0;
}
