#pragma once
#include <stdbool.h>

enum algo {FCFS, RR, PRIORITY, CUSTOM};
extern const char *const algo_name[];

/**
 * this contains the user's options after running opts_init
 */
struct progopts {
    bool per_thread;
    bool verbose;
    enum algo algo;
    char *in_file_name;
};
extern struct progopts opts;

/**
 * print help
 */
void opts_help(char **argv, int exit_status);

/**
 * initialize opts from argc and argv
 */
void opts_init(int argc, char **argv);
