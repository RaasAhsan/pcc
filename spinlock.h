#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <sys/types.h>

typedef struct {
    pid_t* volatile tid;
} spinlock;

void spinlock_lock(spinlock* s);
void spinlock_unlock(spinlock* s);

#endif