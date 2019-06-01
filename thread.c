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

#define STACK_SIZE (1024 * 1024)

void print_pt_info(int i) {
    printf("%d: current PID is: %d\n", i, getpid());
    printf("%d: parent PID is: %d\n", i, getppid());
    printf("%d: thread ID is: %ld\n", i, syscall(SYS_gettid));
}

int task() {
    printf("Started task\n");
    print_pt_info(2);
    sleep(5);
    return 0;
}

void thread_new(thread* t) {
    print_pt_info(1);

    char* stack = malloc(STACK_SIZE);
    char* stackTop = stack + STACK_SIZE;

    // Do we need CLONE_THREAD here? Otherwise we can't wait with join.
    pid_t pid = clone(task, stackTop, CLONE_SIGHAND | CLONE_VM | CLONE_FILES | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID, NULL);
    if (pid == -1) {
        int e = errno;
        perror("The error is: ");
        exit(0);
    }

    t->tid = pid;

    sleep(2);

    printf("Thread ID is %d\n", pid);
}

void thread_join(thread t) {
    printf("Waiting on %d\n", t.tid);
    pid_t p = waitpid(t.tid, NULL, __WCLONE);
    if (p == -1) {
        printf("Error: %d\n", errno);
        perror("Error is: ");
    }
}
