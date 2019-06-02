#include "spinlock.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define SPINLOCK_UNLOCKED 0
#define SPINLOCK_LOCKED 1

void spinlock_new(spinlock* s) {
    s->state = malloc(sizeof(int));
    *(s->state) = SPINLOCK_UNLOCKED;
}

void spinlock_lock(spinlock* s) {
    bool acquired = false;
    while (!acquired) {
        acquired = __sync_bool_compare_and_swap(s->state, SPINLOCK_UNLOCKED, SPINLOCK_LOCKED);
    }

    printf("Acquired\n");
}

void spinlock_unlock(spinlock* s) {
    printf("Releasing\n");
    // TODO: Does this need to be atomic or can it just be a memory write
    __sync_bool_compare_and_swap(s->state, SPINLOCK_LOCKED, SPINLOCK_UNLOCKED);
}

void spinlock_free(spinlock* s) {
    free(s->state);
}
