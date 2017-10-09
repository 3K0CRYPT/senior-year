#pragma once
#include "thread.h"
#include <stdbool.h>

enum event_type {
    THREAD_ARRIVED,
    THREAD_DISPATCH_COMPLETED,
    PROCESS_DISPATCH_COMPLETED,
    CPU_BURST_COMPLETED,
    IO_BURST_COMPLETED,
    THREAD_COMPLETED,
    THREAD_PREEMPTED,
    DISPATCHER_INVOKED
};

extern const char *event_type_name[];

struct event {
    enum event_type type;
    int time;
    struct thread *thread;
    char *msg;
};

struct event * event_init(enum event_type type, int time, struct thread *thread);
bool event_less(void *a, void *b);
