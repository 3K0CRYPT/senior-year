#include "queue.h"
#include <stdlib.h>

struct queue queue() {
    return (struct queue){.head=NULL, .tail=NULL};
}

struct queue * queue_init() {
    struct queue * self = malloc(sizeof(struct queue));
    *self = queue();
    return self;
}

struct queue_node * queue_enqueue(struct queue *self, void *data) {
    struct queue_node *qn = calloc(1,sizeof(struct queue_node));
    struct queue_node *oldhead = self->head;
    self->head = qn;
    self->head->next = oldhead;
    if (oldhead) oldhead->prev = self->head;
    else self->tail = self->head;
    self->head->data = data;
    return self->head;
}

void * queue_dequeue(struct queue *self) {
    if (!self->tail && !self->head) return NULL;
    if (self->head == self->tail) self->head = NULL;
    void * data = self->tail->data;
    self->tail = self->tail->prev;
    if (self->tail) {
        free(self->tail->next);
        self->tail->next = NULL;
    }
    return data;
}

size_t queue_sz(struct queue *self) {
    size_t sz = 0;
    for (struct queue_node *p = self->head; p; p = p->next)
        sz++;
    return sz;
}
