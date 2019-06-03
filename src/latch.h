#ifndef LATCH_H
#define LATCH_H

// TODO: Do these need to be volatile if we atomically modify them?
typedef struct {
    int* volatile state;
    int* volatile remaining;
} latch;

void latch_new(latch* l, int count);
void latch_wait(latch* l);
void latch_countdown(latch* l);
void latch_free(latch* l);

#endif