#include "spinlock.h"

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

void spinlock_lock(spinlock* s) {
    pid_t ctid = getpid();

    bool acquired = false;
    while (!acquired) {
        acquired = __sync_bool_compare_and_swap(s->tid, 0, ctid);
    }
}

void spinlock_unlock(spinlock* s) {
    s->tid = 0;
}
