#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "disruptor.h"
#include "latch.h"
#include "mutex.h"
#include "semaphore.h"
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
    int x = 0;
    while (true) {
        disruptor_put((disruptor*) args, (void*) &x);
        x += 2;
        sleep(5);
    }
}

void thread_two_b(void *args) {
    int x = 1;
    while (true) {
        disruptor_put((disruptor*) args, (void*) &x);
        x += 2;
        sleep(5);
    }
}

void thread_three(void *args) {
    while (true) {
        int* item = (int*) consumer_take((consumer*) args);
        printf("Take: %d\n", *item);
    }
}

int main() {
    printf("size of void* is: %ld\n", sizeof(void*));

    disruptor d;
    disruptor_new(&d, 1024);

    consumer c;
    consumer_new(&c, &d);

    thread ct, p1t, p2t;
    thread_new(&ct, &thread_three, (void*) &c);
    thread_new(&p1t, &thread_two, (void*) &d);
    thread_new(&p2t, &thread_two_b, (void*) &d);

    thread_join(ct);

    consumer_free(&c);
    disruptor_free(&d);

    printf("Done!\n");

    return 0;
}
