#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "spinlock.h"
#include "thread.h"

void thread_two() {
    printf("%d: current PID is: %d\n", 2, getpid());
    sleep(5);
    printf("thread thread 2 is done\n");
}

void thread_three() {
    printf("%d: current PID is: %d\n", 3, getpid());
    sleep(2);
    printf("Thread 3 is done\n");
}

int main() {
    thread a, b;
    thread_new(&a, &thread_two);
    thread_new(&b, &thread_three);

    printf("A: %d\n", a.tid);
    printf("B: %d\n", b.tid);

    thread_join(a);
    // thread_join(b);

    printf("Done joining\n");

    return 0;
}
