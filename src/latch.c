#include "latch.h"

#include <errno.h>
#include <limits.h>
#include <linux/futex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define LATCH_OPEN 0
#define LATCH_CLOSED 1

void latch_new(latch* l, int count) {
    l->state = (int*) malloc(sizeof(int));
    l->remaining = (int*) malloc(sizeof(int));

    *(l->state) = LATCH_OPEN;
    *(l->remaining) = count;
}

void latch_wait(latch* l) {
    while (true) {
        if (*(l->state) == LATCH_CLOSED) {
            break;
        }

        int status = syscall(SYS_futex, l->state, FUTEX_WAIT, LATCH_OPEN, NULL, NULL, 0);
        if (status == -1 && errno != EAGAIN) {
            perror("futex wait");
            exit(1);
        }
    }
}

void latch_countdown(latch* l) {
    if (__sync_sub_and_fetch(l->remaining, 1) > 0) {
        return;
    }

    // TODO: Should this be done atomically?
    *(l->state) = LATCH_CLOSED;

    int status = syscall(SYS_futex, l->state, FUTEX_WAKE, INT_MAX, NULL, NULL, 0);
    if (status == -1) {
        perror("futex wake failed");
        exit(1);
    }
}

void latch_free(latch* l) {
    free(l->state);
    free(l->remaining);
}
