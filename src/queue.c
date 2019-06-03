#include "queue.h"

#include <stdlib.h>

void queue_new(queue* q, int capacity) {
  q->items = malloc(capacity * sizeof(void*));
}

void queue_put(queue* q, void* item) {

}

void queue_take(queue* q) {

}

void queue_free(queue* q) {
  free(q->items);
}
