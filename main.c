#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

int main() {
    printf("Hello world!\n");

    thread* t = malloc(sizeof(thread));
    thread_new(t);
    thread_join(*t);

    return 0;
}
