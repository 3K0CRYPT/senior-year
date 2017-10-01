#include <stdlib.h>
#pragma once

struct Node {
    void *data;
    struct node *next, *previous;
};

struct Queue {
    struct node *head, *tail;
};

// WE NOW USE priority_queue
// this file don't do a damn thing
