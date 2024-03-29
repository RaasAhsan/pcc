#pragma once

typedef struct {
    int* state;
} spinlock;

void spinlock_new(spinlock* s);
void spinlock_lock(spinlock* s);
void spinlock_unlock(spinlock* s);
void spinlock_free(spinlock* s);
