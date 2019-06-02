#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct {
    int* volatile permits;
} semaphore;

void semaphore_new(semaphore* s, int permits);
void semaphore_acquire(semaphore* s);
void semaphore_release(semaphore* s);
void semaphore_free(semaphore* s);

#endif