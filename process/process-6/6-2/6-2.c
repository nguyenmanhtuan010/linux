/*Write a program to see what happens if we try to longjmp() into a function that has
already returned*/
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void second() {
    printf("second\n");
    longjmp(buf, 1);  // Try to jump back to first()
}

void first() {
    if (setjmp(buf) == 0) {
        printf("first\n");
        second();
    } else {
        printf("jumped back\n");
    }
}

int main() {
    first();
    return 0;
}

