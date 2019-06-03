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
    // The next index to read from
    int* volatile reader_index;
    // The next index to write to
    int* volatile writer_index;
} disruptor;

// Invariants: 
// reader_index <= writer_index (mod n)

void disruptor_new(disruptor* d, int capacity);
void disruptor_put(disruptor* d, void* item);
void disruptor_take(disruptor* d);
void disruptor_free(disruptor* d);

#endif