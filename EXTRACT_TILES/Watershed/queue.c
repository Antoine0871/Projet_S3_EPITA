#include <limits.h>
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue* newQueue(unsigned capacity);
int isfull(struct Queue* queue);
int isempty(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
void freeQueue(struct Queue* queue);

struct Queue 
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
struct Queue* newQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->rear = capacity - 1;
    queue->front = queue->size = 0;
 
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
 
int isfull(struct Queue* queue)
{
    return (queue->size == (int)queue->capacity);
}
 
int isempty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
void enqueue(struct Queue* queue, int item)
{
    if (isfull(queue))
    {
	    return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
 
int dequeue(struct Queue* queue)
{
    if (isempty(queue))
    {
	    return INT_MIN;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
int front(struct Queue* queue)
{
    if (isempty(queue))
    {
	    return INT_MIN;
    }
    return queue->array[queue->front];
}

void freeQueue(struct Queue* queue)
{
	free(queue->array);
}
