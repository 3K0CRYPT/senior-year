/**
 * Priority Queue
**/
#pragma once
#include <stdlib.h>
#include <stdbool.h>

/**
 * A single list node, dealt with internally
 */
struct pq_node {
    void *data;
    struct pq_node *next;
};

/**
 * The priority queue structure
 */
struct pq {
    bool (*less)(void *a, void *b);
    struct pq_node *head;
};

struct pq * pq_init(bool (*less)(void *a, void *b));
struct pq_node * pq_node_init(void *data);
void pq_node_del(struct pq_node *self);
void pq_enqueue(struct pq *self, void *data);
void * pq_dequeue(struct pq *self);
