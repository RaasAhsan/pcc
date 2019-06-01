#include "spinlock.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void spinlock_new(spinlock* s) {
    s->tid = malloc(sizeof(pid_t));
}

void spinlock_lock(spinlock* s) {
    pid_t ctid = getpid();

    bool acquired = false;
    while (!acquired) {
        acquired = __sync_bool_compare_and_swap(s->tid, 0, ctid);
    }

    printf("Acquired\n");
}

void spinlock_unlock(spinlock* s) {
    *(s->tid) = 0;
}
