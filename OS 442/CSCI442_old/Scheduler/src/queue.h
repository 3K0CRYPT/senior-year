#pragma once
#include <stdlib.h>

struct queue_node {
    void *data;
    struct queue_node *next, *prev;
};

struct queue {
    struct queue_node *head, *tail;
};

struct queue * queue_init();
struct queue queue();
struct queue_node * queue_enqueue(struct queue *self, void *data);
void * queue_dequeue(struct queue *self);
size_t queue_sz(struct queue *self);
