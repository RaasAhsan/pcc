#ifndef THREAD_H
#define THREAD_H

#include <sys/types.h>

typedef struct {
    pid_t tid;
} thread;

void thread_new(thread* t, void (*fn)());
void thread_join(thread t);

#endif