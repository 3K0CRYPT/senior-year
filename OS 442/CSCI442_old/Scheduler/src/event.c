#include "event.h"
#include <stdlib.h>
#include <stdbool.h>

const char *event_type_name[] = {
    "THREAD_ARRIVED",
    "THREAD_DISPATCH_COMPLETED",
    "PROCESS_DISPATCH_COMPLETED",
    "CPU_BURST_COMPLETED",
    "IO_BURST_COMPLETED",
    "THREAD_COMPLETED",
    "THREAD_PREEMPTED",
    "DISPATCHER_INVOKED"
};

struct event * event_init(enum event_type type, int time, struct thread *thread) {
    struct event *self = malloc(sizeof(struct event));
    self->type = type;
    self->time = time;
    self->thread = thread;
    self->msg = NULL;
    return self;
}

bool event_less(void *a, void *b) {
    struct event *event_a = a, *event_b = b;
    return event_a->time < event_b->time;
}
