#include "pq.h"
#include <stdlib.h>
#include <stdbool.h>

struct pq * pq_init(bool (*less)(void *a, void *b)) {
    struct pq * self = malloc(sizeof(struct pq));
    self->less = less;
    self->head = NULL;
    return self;
}

struct pq_node * pq_node_init(void *data) {
    struct pq_node * self = malloc(sizeof(struct pq_node));
    self->data = data;
    self->next = NULL;
    return self;
}

void pq_enqueue(struct pq *self, void *data) {
    struct pq_node *oldhead = self->head;
    self->head = pq_node_init(data);
    self->head->next = oldhead;
}

void * pq_dequeue(struct pq *self) {
    struct pq_node *least = self->head, *parent = NULL;
    for (struct pq_node *p = least, *lp = NULL; p; lp = p, p = p->next) {
        if (self->less(p->data, least->data)) {
            least = p;
            parent = lp;
        }
    }
    if (!least) return NULL;
    void *data = least->data;
    if (parent) parent->next = least->next;
    else self->head = least->next;
    free(least);
    return data;
}
