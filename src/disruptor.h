#ifndef DISRUPTOR_H
#define DISRUPTOR_H

/*
SPSC (Single Producer, Single Consumer)
SPMC (Single Producer, Multiple Consumer)
MPSC (Multiple Producer, Single Consumer)
MPMC (Multiple Producer, Multiple Consumer)
*/

typedef struct {
    int capacity;
    // An array of length `capacity` that forms the underlying circular buffer
    void** volatile items;
    int* volatile claimed_sequence;
    int* volatile sequence;
} disruptor;

void disruptor_new(disruptor* d, int capacity);
void disruptor_put(disruptor* d, void* item);
void disruptor_take(disruptor* d);
void disruptor_free(disruptor* d);

#endif