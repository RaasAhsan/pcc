#include "spinlock.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void spinlock_new(spinlock* s) {
    s->state = malloc(sizeof(int));
}

void spinlock_lock(spinlock* s) {
    bool acquired = false;
    while (!acquired) {
        acquired = __sync_bool_compare_and_swap(s->state, 0, 1);
    }

    printf("Acquired\n");
}

void spinlock_unlock(spinlock* s) {
    printf("Releasing\n");
    __sync_bool_compare_and_swap(s->state, 1, 0);
}

void spinlock_free(spinlock* s) {
    free(s->state);
}
