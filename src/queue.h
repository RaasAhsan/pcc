#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
  void** items;
  
} queue;

void queue_new(queue* q, int capacity);
void queue_put(queue* q, void* item);
void queue_take(queue* q); // does void** make sense here?
void queue_free(queue* q);

#endif