#pragma once

#include <sys/types.h>

typedef struct {
    pid_t tid;
} thread;

void thread_new(thread* t, void (*fn)(), void *args);
void thread_join(thread t);
