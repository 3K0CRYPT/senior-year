#include <stdlib.h>
#pragma once

enum burst_type {CPU, IO};
extern const char *burst_type_name[];

struct burst {
    enum burst_type type;
    size_t length;
};

struct burst * burst_init(enum burst_type type, size_t length);
