#ifndef QUEUE_H_
#define QUEUE_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue* newQueue(unsigned capacity);
int isfull(struct Queue* queue);
int isempty(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
void freeQueue(struct Queue* queue);

#endif

