#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "../Stack/stack.h"

typedef struct {
    Stack *Stack1;
    Stack *Stack2;
} Queue;

void enqueue(Queue *queue, int i);
int dequeue(Queue *queue);
void print_queue(Queue *queue);
bool queue_is_empty(Queue *queue);
void empty_queue(Queue *queue);
int queue_size(Queue *queue);
int queue_peek(Queue *queue);

#endif
