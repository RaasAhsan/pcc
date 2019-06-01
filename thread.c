#define _GNU_SOURCE

#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "thread.h"

#define STACK_SIZE (2 * 1024 * 1024)

typedef struct {
    void (*fn)();
    void *args;
} run_thread_args;

int run_thread(void *args) {
    run_thread_args* rtargs = (run_thread_args*) args;
    (*(rtargs->fn))(rtargs->args);
    return 0;
}

void thread_new(thread* t, void (*fn)(), void *args) {
    char* stack = malloc(STACK_SIZE);
    char* stackTop = stack + STACK_SIZE;

    // TODO: We should free this in run_thread.
    run_thread_args* rtargs = malloc(sizeof(run_thread_args));
    rtargs->fn = fn;
    rtargs->args = args; // May need to copy this memory

    // Do we need CLONE_THREAD here? Otherwise we can't wait with join.
    pid_t pid = clone(run_thread, stackTop, CLONE_SIGHAND | CLONE_VM | CLONE_FILES | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID, (void*) rtargs);
    if (pid == -1) {
        int e = errno;
        perror("The error is: ");
        exit(0);
    }

    t->tid = pid;
}

void thread_join(thread t) {
    printf("Waiting on %d\n", t.tid);
    pid_t p = waitpid(t.tid, NULL, __WCLONE);
    if (p == -1) {
        printf("Error: %d\n", errno);
        perror("Error is: ");
    }
}
