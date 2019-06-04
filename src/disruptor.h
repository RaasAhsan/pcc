#pragma once

/*
SPSC (Single Producer, Single Consumer)
SPMC (Single Producer, Multiple Consumer)
MPSC (Multiple Producer, Single Consumer)
MPMC (Multiple Producer, Multiple Consumer)
*/

typedef struct {
    // An array of length `capacity` that forms the underlying circular buffer
    void** volatile items;
    int volatile capacity;
    // The next sequence number to be claimed
    int* volatile claim_sequence;
    // The next sequence number to be committed
    int* volatile commit_sequence;
} disruptor;

void disruptor_new(disruptor* d, int capacity);
void disruptor_put(disruptor* d, void* item);
void disruptor_free(disruptor* d);

// Single-threaded consumer

typedef struct {
    disruptor* disruptor;
    int* commit_sequence;
} consumer;

void consumer_new(consumer* c, disruptor* d);
void* consumer_take(consumer* c);
// TODO: Perform a batching read
void consumer_free(consumer* c);
