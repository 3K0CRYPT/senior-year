#include <stdlib.h>
#include "burst.h"
const char *burst_type_name[] = {"CPU", "IO"};
struct burst * burst_init(enum burst_type type, size_t length) {
    struct burst *new_burst = malloc(sizeof(struct burst));
    new_burst->type = type;
    new_burst->length = length;
    return new_burst;
}
