#include "mutex.h"

#include <errno.h>
#include <linux/futex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void mutex_new(mutex* m) {
    m->state = malloc(sizeof(int));
}

void mutex_lock(mutex* m) {
    pid_t ctid = getpid();

    bool acquired = false;
    while (!acquired) {
        acquired = __sync_bool_compare_and_swap(m->state, 0, 1);

        if (!acquired) {
          int status = syscall(SYS_futex, m->state, FUTEX_WAIT, 1, NULL, NULL, 0);
          if (status == -1 && errno != EAGAIN) {
              perror("futex wait");
              exit(1);
          }
        }
    }

    printf("Acquired\n");
}

void mutex_unlock(mutex* m) {
    printf("Releasing\n");
    *(m->state) = 0;
    int status = syscall(SYS_futex, m->state, FUTEX_WAKE, 1, NULL, NULL, 0);
    if (status == -1) {
        perror("futex wake failed");
        exit(1);
    }
}

void mutex_free(mutex* m) {
    free(m->state);
}
