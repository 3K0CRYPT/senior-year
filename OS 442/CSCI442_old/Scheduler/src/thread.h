#pragma once
#include <stdlib.h>
#include "queue.h"

enum thread_state {NEW, READY, RUNNING, BLOCKED, EXIT};
extern const char *const thread_state_name[];

struct thread {
    struct process *parent;
    struct queue bursts;
    enum thread_state current_state, last_state;
    size_t time_slice;
    size_t arrival_time;
    size_t start_time;
    size_t end_time;
    size_t service_time;
    size_t io_time;
    size_t last_start;
    size_t last_block;
    size_t feedback_offset;
};

struct thread thread();
void thread_set_ready(struct thread *self, size_t time);
void thread_set_running(struct thread *self, size_t time);
void thread_set_blocked(struct thread *self, size_t time);
void thread_set_exit(struct thread *self, size_t time);
size_t thread_trt(struct thread *self);
size_t thread_res(struct thread *self);
