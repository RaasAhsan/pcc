#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "spinlock.h"
#include "thread.h"

void thread_two(void *args) {
    printf("%d: current PID is: %d\n", 2, getpid());
    sleep(5);
    printf("Thread 2 is done %d\n", *((int*) args));
}

void thread_three(void *args) {
    printf("%d: current PID is: %d\n", 3, getpid());
    sleep(2);
    printf("Thread 3 is done %d\n", *((int*) args));
}

int main() {
    thread a, b;
    int x = 5;
    int y = 6;
    thread_new(&a, &thread_two, (void*) &x);
    thread_new(&b, &thread_three, (void*) &y);

    printf("A: %d\n", a.tid);
    printf("B: %d\n", b.tid);

    thread_join(a);
    thread_join(b);

    printf("Done joining\n");

    return 0;
}
