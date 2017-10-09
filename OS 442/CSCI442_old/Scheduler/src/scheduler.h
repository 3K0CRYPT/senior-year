#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "event.h"
#include "pq.h"
#include "queue.h"
#include "process.h"

struct scheduler {
    FILE *in;
    FILE *out;
    int num_processes,
        thread_overhead,
        process_overhead;
    struct pq *events;
    struct process *processes;
    struct process *processes_top;
    size_t total_dispatch;
    union {
        struct queue fcfs_queue;
        struct queue rr_queue;
    };
    struct queue *multiq;
    size_t multiq_sz;
};

extern struct thread *active_thread, *last_thread;

int scheduler(struct scheduler *self);
void read_process(struct scheduler *self);
void read_event(struct scheduler *self, struct thread *p);
void verbose_event(struct scheduler *self, struct event *event);
void sch_readyq(struct scheduler *self, struct event *ev, struct thread *th);
struct thread * sch_next(struct scheduler *self, struct event *ev);
void statistics(struct scheduler *self);
void per_thread(struct scheduler *self);
