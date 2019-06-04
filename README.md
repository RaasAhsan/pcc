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
./compile.sh
./a.out
```

## Running with docker

```
docker build -t pcc-dev .
docker run -it pcc-dev ./a.out
```