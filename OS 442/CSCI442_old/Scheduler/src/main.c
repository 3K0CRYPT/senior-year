/**
 * CSCI-442: Operating Systems
 */
#include <stdio.h>
#include <stdlib.h>
#include "opts.h"
#include "scheduler.h"

int main(int argc, char **argv) {
    opts_init(argc, argv);
    struct scheduler s;
    s.in = fopen(opts.in_file_name, "r");
    if (!s.in) {
        perror(opts.in_file_name);
        return 1;
    }
    s.out = stdout;
    return scheduler(&s);
}
