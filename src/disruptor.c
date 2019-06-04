#include "disruptor.h"

#include <stdbool.h>
#include <stdlib.h>

void disruptor_new(disruptor* d, int capacity) {
    d->items = (void**) malloc(capacity * sizeof(void*));
    d->capacity = capacity;
    d->claim_sequence = (int*) malloc(sizeof(int));
    d->commit_sequence = (int*) malloc(sizeof(int));
}

void disruptor_put(disruptor* d, void* item) {
    // A CAS is only necessary when there is contention on the claim sequence by multiple producers
    int claimed_sequence = __sync_fetch_and_add(d->claim_sequence, 1);
    d->items[claimed_sequence] = item;
    // Logically, a write barrier is necessary here. We are reusing the first one in the loop.

    while (true) {
        // Wait until the committed sequence is the sequence that this producer claimed
        __sync_synchronize();
        if (*(d->commit_sequence) == claimed_sequence) {
            *(d->commit_sequence) = claimed_sequence + 1;
            __sync_synchronize();
            break;
        }

        // We have several choices here:
        // 1. Do nothing: busy-spin on the CPU
        // 2. Wait on a futex signaled by other producers
    }
}

void disruptor_free(disruptor* d) {
    free(d->items);
    free(d->claim_sequence);
    free(d->commit_sequence);
}

void consumer_new(consumer* c, disruptor* d) {
    c->disruptor = d;
    c->commit_sequence = (int*) malloc(sizeof(int));
    *(c->commit_sequence) = -1;
}

void* consumer_take(consumer* c) {
    while (true) {
        __sync_synchronize();
        if (*(c->commit_sequence) < *(c->disruptor->commit_sequence) - 1) {
            *(c->commit_sequence) = *(c->commit_sequence) + 1;
            return c->disruptor->items[*(c->commit_sequence)];
        }
    }
}

void consumer_free(consumer* c) {
    free(c->commit_sequence);
}
