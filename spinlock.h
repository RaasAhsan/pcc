#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <sys/types.h>

typedef struct {
    pid_t* volatile tid;
} spinlock;

void spinlock_new(spinlock* s);
void spinlock_lock(spinlock* s);
void spinlock_unlock(spinlock* s);
void spinlock_free(spinlock* s);

#endif