#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "spinlock.h"
#include "thread.h"

void thread_two(void *args) {
    spinlock_lock((spinlock*) args);
    printf("%d: current PID is: %d\n", 2, getpid());
    sleep(5);
    printf("Thread 2 is done %d\n", 1);
    spinlock_unlock((spinlock*) args);
}

void thread_three(void *args) {
    spinlock_lock((spinlock*) args);
    printf("%d: current PID is: %d\n", 3, getpid());
    sleep(2);
    printf("Thread 3 is done %d\n", 2);
    spinlock_unlock((spinlock*) args);
}

int main() {
    int x = 5;
    int y = 6;

    thread a, b;
    spinlock s;
    spinlock_new(&s);

    thread_new(&a, &thread_two, (void*) &s);
    thread_new(&b, &thread_three, (void*) &s);


    printf("A: %d\n", a.tid);
    // printf("B: %d\n", b.tid);

    thread_join(a);
    thread_join(b);

    printf("Done joining\n");

    spinlock_free(&s);

    return 0;
}
