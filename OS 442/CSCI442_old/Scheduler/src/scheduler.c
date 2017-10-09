#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "scheduler.h"
#include "opts.h"
#include "process.h"
#include "event.h"
#include "burst.h"


struct thread *last_thread = NULL;
struct thread *active_thread = NULL;

int scheduler(struct scheduler *self) {
    self->events = pq_init(event_less);
    self->fcfs_queue = queue();
    if (opts.algo == PRIORITY) {
        self->multiq_sz = 4;
        self->multiq = malloc(4*sizeof(struct queue));
        for (int i = 0; i < 4; i++) {
            self->multiq[i] = queue();
        }
    }
    if (opts.algo == CUSTOM) {
        self->multiq_sz = 12;
        self->multiq = malloc(12*sizeof(struct queue));
        for (int i = 0; i < 12; i++) {
            self->multiq[i] = queue();
        }
    }
    self->total_dispatch = 0;
    fscanf(self->in, "%d %d %d",
            &self->num_processes,
            &self->thread_overhead,
            &self->process_overhead
      );
    self->processes = malloc(self->num_processes*sizeof(struct process));
    self->processes_top = self->processes;
    for (int i = 0; i < self->num_processes; i++)
        read_process(self);
    struct event *ev = pq_dequeue(self->events);
    while (ev) {
        switch (ev->type) {
            case THREAD_ARRIVED:
                thread_set_ready(ev->thread, ev->time);
                sch_readyq(self, ev, ev->thread);
                if (!active_thread)
                    pq_enqueue(self->events, (void *)event_init(DISPATCHER_INVOKED, ev->time, NULL));
                break;
            case DISPATCHER_INVOKED:
                assert(!active_thread);
                struct thread *next = sch_next(self, ev);
                if (next) {
                    ev->thread = next;
                    if (last_thread && next->parent == last_thread->parent) {
                        /* Thread switch */
                        self->total_dispatch += self->thread_overhead;
                        pq_enqueue(self->events,
                                (void *)event_init(
                                    THREAD_DISPATCH_COMPLETED,
                                    ev->time + self->thread_overhead,
                                    next
                                )
                            );
                    }
                    else {
                        /* Process switch */
                        self->total_dispatch += self->process_overhead;
                        pq_enqueue(self->events,
                                (void *)event_init(
                                    PROCESS_DISPATCH_COMPLETED,
                                    ev->time + self->process_overhead,
                                    next
                                )
                            );
                    }
                    active_thread = next;
                }
                break;
            case PROCESS_DISPATCH_COMPLETED:
            case THREAD_DISPATCH_COMPLETED:
                assert(active_thread == ev->thread);
                last_thread = active_thread;
                active_thread = NULL;
                thread_set_running(ev->thread, ev->time);
                struct burst *cpu_burst = ev->thread->bursts.tail->data;
                assert(cpu_burst->type == CPU);
                if (ev->thread->time_slice < cpu_burst->length) {
                    /* We will need to preempt */
                    pq_enqueue(self->events,
                            (void *)event_init(
                                THREAD_PREEMPTED,
                                ev->time + ev->thread->time_slice,
                                ev->thread
                            )
                        );
                }
                else {
                    /* Burst will complete in time slice */
                    pq_enqueue(self->events,
                            (void *)event_init(
                                CPU_BURST_COMPLETED,
                                ev->time + cpu_burst->length,
                                ev->thread
                            )
                        );
                }
                break;
            case CPU_BURST_COMPLETED:
                queue_dequeue(&ev->thread->bursts);
                if (ev->thread->bursts.tail) {
                    /* There are still bursts left */
                    thread_set_blocked(ev->thread, ev->time);
                    struct burst *io_burst = ev->thread->bursts.tail->data;
                    assert(io_burst->type == IO);
                    pq_enqueue(self->events,
                            (void *)event_init(
                                IO_BURST_COMPLETED,
                                ev->time + io_burst->length,
                                ev->thread
                            )
                        );
                    pq_enqueue(self->events, (void *)event_init(DISPATCHER_INVOKED, ev->time, NULL));
                }
                else {
                    /* No more bursts */
                    ev->msg = (char *)"No more bursts remain in this thread";
                    pq_enqueue(self->events,
                            (void *)event_init(
                                THREAD_COMPLETED,
                                ev->time,
                                ev->thread
                            )
                        );
                }
                break;
            case IO_BURST_COMPLETED:
                thread_set_ready(ev->thread, ev->time);
                sch_readyq(self, ev, ev->thread);
                struct burst *io_burst = queue_dequeue(&ev->thread->bursts);
                assert(io_burst->type == IO);
                if (!active_thread)
                    pq_enqueue(self->events, (void *)event_init(DISPATCHER_INVOKED, ev->time, NULL));
                break;
            case THREAD_COMPLETED:
                thread_set_exit(ev->thread, ev->time);
                pq_enqueue(self->events, (void *)event_init(DISPATCHER_INVOKED, ev->time, NULL));
                break;
            case THREAD_PREEMPTED:
                thread_set_ready(ev->thread, ev->time);
                struct burst *pre_burst = ev->thread->bursts.tail->data;
                assert(pre_burst->type == CPU);
                ev->thread->feedback_offset++;
                pre_burst->length -= 3;
                sch_readyq(self, ev, ev->thread);
                pq_enqueue(self->events, (void *)event_init(DISPATCHER_INVOKED, ev->time, NULL));
                break;
            default:
                assert(false); /* something went horribly wrong */
                break;
        }
        verbose_event(self, ev);
        ev = pq_dequeue(self->events);
    }
    per_thread(self);
    statistics(self);
    return 0;
}

void read_process(struct scheduler *self) {
    int proc_typ;
    fscanf(self->in, " %d %d %lu",
            &self->processes_top->pid,
            &proc_typ,
            &self->processes_top->threads_sz
        );
    self->processes_top->type = proc_typ;
    self->processes_top->threads = malloc(
            self->processes_top->threads_sz*sizeof(struct thread)
        );
    for (struct thread *p = self->processes_top->threads;
            p < self->processes_top->threads + self->processes_top->threads_sz;
            p++) {
        *p = thread();
        p->parent = self->processes_top;
        read_event(self, p);
    }
    self->processes_top++;
}

void read_event(struct scheduler *self, struct thread *p) {
    int num_bursts, time;
    fscanf(self->in, " %d %d", &time, &num_bursts);
    for (int i = 0; i < num_bursts; i++) {
        int cpu_burst, io_burst;
        fscanf(self->in, num_bursts-i==1?" %d":" %d %d",
                &cpu_burst,
                &io_burst
          );
        queue_enqueue(&p->bursts, burst_init(CPU, cpu_burst));
        if (num_bursts-i!=1)
            queue_enqueue(&p->bursts, burst_init(IO, io_burst));

    }
    pq_enqueue(self->events, (void *)event_init(THREAD_ARRIVED, time, p));
}

void verbose_event(struct scheduler *self, struct event *event) {
    if (!opts.verbose) return;
    fprintf(self->out, "At time %d:\n"
            "    %s\n",
            event->time,
            event_type_name[event->type]
       );
    if (event->thread) {
        fprintf(self->out,
            "    Thread %ld in process %d [%s]\n",
            event->thread - event->thread->parent->threads,
            event->thread->parent->pid,
            process_type_name[event->thread->parent->type]
        );
    }
    if (event->msg) {
        fprintf(self->out, "    %s\n", event->msg);
    }
    else if (event->thread) {
        fprintf(self->out, "    Tranistioned from %s to %s\n",
                thread_state_name[event->thread->last_state],
                thread_state_name[event->thread->current_state]
           );
    }
    fputc('\n', self->out);
}

/**
 * Add to the ready queues of the user specified scheduler
 */
void sch_readyq(struct scheduler *self, struct event *ev, struct thread *th) {
    int queueno;
    switch (opts.algo) {
        case FCFS:
            queue_enqueue(&self->fcfs_queue, (void *)th);
            break;
        case RR:
            queue_enqueue(&self->rr_queue, (void *)th);
            break;
        case PRIORITY:
            queue_enqueue(self->multiq + th->parent->type, (void *)th);
            break;
        case CUSTOM:
            queueno = th->parent->type + th->feedback_offset;
            if (queueno > 11) queueno = 11;
            queue_enqueue(self->multiq + queueno, (void *)th);
            break;
        default:
            assert(0);
    }
}

/**
 * Get the next thread to run from the schedluer
 */
struct thread * sch_next(struct scheduler *self, struct event *ev) {
    static char msg[128];
    int q_sz = 0, i;
    struct thread *th = NULL;
    switch (opts.algo) {
        case FCFS:
            q_sz = queue_sz(&self->fcfs_queue);
            th = queue_dequeue(&self->fcfs_queue);
            if (th) {
                assert(th->current_state == READY);
                snprintf(msg, sizeof(msg),
                        "Selected from %d threads; will run to completion of burst", q_sz);
            }
            else snprintf(msg, sizeof(msg), "No threads are READY");
            break;
        case RR:
            q_sz = queue_sz(&self->rr_queue);
            th = queue_dequeue(&self->rr_queue);
            if (th) {
                assert(th->current_state == READY);
                snprintf(msg, sizeof(msg),
                        "Selected from %d threads; will run for time slice or completion", q_sz);
                th->time_slice = 3;
            }
            else snprintf(msg, sizeof(msg), "No threads are READY");
            break;
        case PRIORITY:
            for (i = 0; i < 4; i++) {
                q_sz = queue_sz(self->multiq + i);
                if (q_sz) {
                    th = queue_dequeue(self->multiq + i);
                    snprintf(msg, sizeof(msg),
                        "Selected from %d %s threads; will run to completion of burst",
                            q_sz,
                            process_type_name[i]
                        );
                    ev->msg = msg;
                    return th;
                }
            }
            snprintf(msg, sizeof(msg), "No threads are READY");
            break;
        case CUSTOM:
            for (i = 0; i < 12; i++) {
                q_sz = queue_sz(self->multiq + i);
                if (q_sz) {
                    th = queue_dequeue(self->multiq + i);
                    snprintf(msg, sizeof(msg),
                        "Selected from %d (Queue %d) threads; will run to completion of burst",
                            q_sz,
                            i + 1
                        );
                    ev->msg = msg;
                    th->time_slice = 3;
                    return th;
                }
            }
            snprintf(msg, sizeof(msg), "No threads are READY");
            break;
        default:
            assert(0);
    }
    if (*msg) ev->msg = msg;
    return th;
}

void statistics(struct scheduler *self) {
    fprintf(self->out, "SIMULATION COMPLETED!\n\n");
    size_t min_arrival = -1, max_end = 0, service = 0, io = 0;
    for (enum process_type i = SYSTEM; i < 4; i++) {
        int total_count = 0;
        double trt_sum = 0, res_sum = 0;
        for (struct process *p = self->processes; p < self->processes_top; p++) {
            if (p->type == i) {
                for (struct thread *th = p->threads; th < p->threads + p->threads_sz; th++) {
                    if (th->arrival_time < min_arrival) min_arrival = th->arrival_time;
                    if (th->end_time > max_end) max_end = th->end_time;
                    total_count++;
                    trt_sum += thread_trt(th);
                    res_sum += thread_res(th);
                    service += th->service_time;
                    io += th->io_time;
                }
            }
        }
        fprintf(self->out, "%s THREADS:\n"
               "    Total count:         %8d\n"
               "    Avg response time:   %8.2f\n"
               "    Avg turnaround time: %8.2f\n"
               "\n",
               process_type_name[i],
               total_count,
               total_count? res_sum / total_count : 0.0,
               total_count? trt_sum / total_count : 0.0
          );
    }
    fprintf(self->out,
            "Total elapsed time:  %12lu\n"
            "Total service time:  %12lu\n"
            "Total I/O time:      %12lu\n"
            "Total dispatch time: %12lu\n"
            "Total idle time:     %12lu\n"
            "\n"
            "CPU utilisation:    %12.2f%%\n"
            "CPU efficiency:     %12.2f%%\n",
            max_end - min_arrival,
            service,
            io,
            self->total_dispatch,
            (max_end - min_arrival) - service - self->total_dispatch,
            (service + self->total_dispatch) / (double)(max_end - min_arrival) * 100,
            service / (double)(max_end - min_arrival) * 100
       );
}

void per_thread(struct scheduler *self) {
    if (!opts.per_thread) return;
    for (struct process *p = self->processes; p < self->processes_top; p++) {
        fprintf(self->out, "Process %d [%s]:\n", p->pid, process_type_name[p->type]);
        for (struct thread *th = p->threads; th < p->threads + p->threads_sz; th++) {
            fprintf(self->out,
                    "    Thread %lu:  ARR: %-6lu CPU: %-6lu I/O: %-6lu TRT: %-6lu END: %lu\n",
                    th - p->threads,
                    th->arrival_time,
                    th->service_time,
                    th->io_time,
                    thread_trt(th),
                    th->end_time
               );
        }
        fputc('\n', self->out);
    }
}
