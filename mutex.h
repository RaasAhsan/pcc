#ifndef MUTEX_H
#define MUTEX_H

typedef struct {
    int* volatile state;
} mutex;

void mutex_new(mutex* m);
void mutex_lock(mutex* m);
void mutex_unlock(mutex* m);
void mutex_free(mutex* m);

#endif