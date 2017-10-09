# Shadow Recruit Scheduler

This is a Scheduler that meets the project requirements. It was written by Jack
Rosenthal, more commonly known as Shadow Recruit.

List of files and what they do:

    src/main.c                  The entry point into the program
        opts.{c,h}              Structure for reading and parsing arguments
        scheduler.{c,h}         The core of the simulation and implementation
                                of algorithms
        event.{c,h}             Event structure
        process.{c,h}           Process structure
        thread.{c,h}            Thread structure
        burst.{c,h}             Burst structure
        queue.{c,h}             Queue data structure implemented using linked
                                lists
        pq.{c,h}                Priority queue data structure, also using
                                linked lists

## Unusual features

Written in C (wait, what? I mean C++... cough cough). Also rarely frees memory,
makes Google Chrome look good.

## Time spent on project

Approx 8 hours maybe? I'm not very good at keeping track of time.

## My Custom Algorithm

My `CUSTOM` algorithm is a Mulilevel Feedback Queue, using 12 queues for
preemption.

 * For use of priority, processes of `SYSTEM` priority start in Queue 1,
   `INTERACTIVE` in 2, and so forth.
 * The algorithm optimises threads with short CPU bursts (IO bound threads) as
   the preemption causes the queue to be advanced.
 * Threads are preempted on a time slice of 3
 * 12 queues are used, so there are definately at least 6 queues being used.
 * Starvation is possible for CPU bound processes, for a `BATCH` CPU bound
   process, life just sucks.
 * Algoritm is not fair, it's a feedback queue.

