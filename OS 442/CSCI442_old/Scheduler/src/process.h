#pragma once
#include <stdlib.h>
#include "thread.h"

enum process_type {SYSTEM, INTERACTIVE, NORMAL, BATCH};

const static char process_type_name[4][12] =
    {"SYSTEM", "INTERACTIVE", "NORMAL", "BATCH"};

struct process {
    int pid;
    enum process_type type;
    size_t threads_sz;
    struct thread *threads;
};
