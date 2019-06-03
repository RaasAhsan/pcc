#!/bin/bash

gcc src/main.c src/disruptor.c src/latch.c src/mutex.c src/queue.c src/semaphore.c src/spinlock.c src/thread.c
