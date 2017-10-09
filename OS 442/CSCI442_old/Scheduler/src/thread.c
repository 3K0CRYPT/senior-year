#include "scheduler.h"
#include "thread.h"
#include "process.h"
#include "queue.h"
#include <assert.h>

const char *const thread_state_name[] =
    {"NEW", "READY", "RUNNING", "BLOCKED", "EXIT"};

struct thread thread() {
    struct thread th;
    th.bursts = queue();
    th.last_state = 5;
    th.current_state = NEW;
    th.arrival_time = -1;
    th.start_time = -1;
    th.end_time = -1;
    th.service_time = 0;
    th.io_time = 0;
    th.time_slice = -1;
    th.last_start = -1;
    th.last_block = -1;
    th.feedback_offset = 0;
    return th;
}

void thread_set_ready(struct thread *self, size_t time) {
    assert(self->current_state == NEW
        || self->current_state == RUNNING
        || self->current_state == BLOCKED);
    if (self->current_state == RUNNING) {
        assert(active_thread == self);
        active_thread = NULL;
        self->service_time += time - self->last_start;
    }
    if (self->current_state == BLOCKED)
        self->io_time += time - self->last_block;
    self->last_state = self->current_state;
    self->current_state = READY;
    if (self->arrival_time == -1)
        self->arrival_time = time;
}

void thread_set_running(struct thread *self, size_t time) {
    assert(self->current_state == READY && !active_thread);
    self->last_state = READY;
    self->current_state = RUNNING;
    if (self->start_time == -1)
        self->start_time = time;
    self->last_start = time;
    active_thread = self;
}

void thread_set_blocked(struct thread *self, size_t time) {
    assert(self->current_state == RUNNING && active_thread);
    self->service_time += time - self->last_start;
    self->last_state = RUNNING;
    self->current_state = BLOCKED;
    self->last_block = time;
    active_thread = NULL;
}

void thread_set_exit(struct thread *self, size_t time) {
    assert(self->current_state == RUNNING && active_thread
            && self->end_time == -1);
    self->service_time += time - self->last_start;
    self->last_state = RUNNING;
    self->current_state = EXIT;
    self->end_time = time;
    active_thread = NULL;
}

size_t thread_trt(struct thread *self) {
    return self->end_time - self->arrival_time;
}

size_t thread_res(struct thread *self) {
    return self->start_time - self->arrival_time;
}
