#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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
    mutex_lock((mutex*) args);
    printf("%d: current PID is: %d\n", 2, getpid());
    sleep(5);
    printf("Thread 2 is done %d\n", 1);
    mutex_unlock((mutex*) args);
}

void thread_three(void *args) {
    mutex_lock((mutex*) args);
    printf("%d: current PID is: %d\n", 3, getpid());
    sleep(2);
    printf("Thread 3 is done %d\n", 2);
    mutex_unlock((mutex*) args);
}

int main() {
    int x = 5;
    int y = 6;

    spinlock s;
    spinlock_new(&s);

    mutex m;
    mutex_new(&m);

    thread a, b;
    thread_new(&a, &thread_two, (void*) &m);
    thread_new(&b, &thread_three, (void*) &m);


    printf("A: %d\n", a.tid);
    // printf("B: %d\n", b.tid);

    thread_join(a);
    thread_join(b);

    spinlock_free(&s);
    mutex_free(&m);

    return 0;
}
