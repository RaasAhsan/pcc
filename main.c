#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "latch.h"
#include "mutex.h"
#include "spinlock.h"
#include "thread.h"

// void thread_two(void *args) {
//     spinlock_lock((spinlock*) args);
//     printf("%d: current PID is: %d\n", 2, getpid());
//     sleep(5);
//     printf("Thread 2 is done %d\n", 1);
//     spinlock_unlock((spinlock*) args);
// }

// void thread_three(void *args) {
//     spinlock_lock((spinlock*) args);
//     printf("%d: current PID is: %d\n", 3, getpid());
//     sleep(2);
//     printf("Thread 3 is done %d\n", 2);
//     spinlock_unlock((spinlock*) args);
// }

void thread_two(void *args) {
    printf("Starting two\n");
    sleep(5);
    printf("Thread 2 is done %d\n", 2);
    latch_countdown((latch*) args);
}

void thread_three(void *args) {
    printf("Starting three\n");
    sleep(2);
    printf("Thread 3 is done %d\n", 3);
    latch_countdown((latch*) args);
}

int main() {
    int x = 5;
    int y = 6;

    latch l;
    latch_new(&l, 2);

    thread a, b;
    thread_new(&a, &thread_two, (void*) &l);
    thread_new(&b, &thread_three, (void*) &l);

    latch_wait(&l);

    printf("Done!\n");

    return 0;
}
