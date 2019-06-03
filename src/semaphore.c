#include "semaphore.h"

#include <errno.h>
#include <linux/futex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

void semaphore_new(semaphore* s, int permits) {
    s->permits = (int*) malloc(sizeof(int));
    *(s->permits) = permits;
}

void semaphore_acquire(semaphore* s) {
    while (true) {
        int permits = *(s->permits);
        if (permits > 0) {
            if (__sync_bool_compare_and_swap(s->permits, permits, permits-1)) {
                break;
            }
        } else {
            int status = syscall(SYS_futex, s->permits, FUTEX_WAIT, 0, NULL, NULL, 0);
            if (status == -1 && errno != EAGAIN) {
                perror("futex wait");
                exit(1);
            }
        }
    }
}

void semaphore_release(semaphore* s) {
    __sync_add_and_fetch(s->permits, 1);

    int status = syscall(SYS_futex, s->permits, FUTEX_WAKE, 1, NULL, NULL, 0);
    if (status == -1) {
        perror("futex wake failed");
        exit(1);
    }
}

void semaphore_free(semaphore* s) {
    free(s->permits);
}
