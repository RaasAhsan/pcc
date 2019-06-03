# pcc

pcc is a library for concurrent programming in C. It provides the following mechanisms:
- Threads
- Mutexes
- Semaphores
- Latches
- Barriers
- Atomics
- Spinlock
- Reentrant locks
- Queues
- Disruptor

## Running

```shell
gcc main.c thread.c spinlock.c mutex.c latch.c queue.c semaphore.c && ./a.out
```
