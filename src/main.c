#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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
    semaphore_acquire((semaphore*) args);
    printf("Starting two\n");
    sleep(5);
    printf("Thread 2 is done %d\n", 2);
    semaphore_release((semaphore*) args);
}

void thread_three(void *args) {
    semaphore_acquire((semaphore*) args);
    printf("Starting three\n");
    sleep(2);
    printf("Thread 3 is done %d\n", 3);
    semaphore_release((semaphore*) args);
}

int main() {
    printf("size of void* is: %ld\n", sizeof(void*));
    int x = 5;
    int y = 6;

    semaphore s;
    semaphore_new(&s, 1);

    thread a, b;
    thread_new(&a, &thread_two, (void*) &s);
    thread_new(&b, &thread_three, (void*) &s);

    thread_join(a);
    thread_join(b);

    semaphore_free(&s);

    printf("Done!\n");

    return 0;
}
