#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include "opts.h"

const char *const algo_name[] = {"FCFS", "RR", "PRIORITY", "CUSTOM"};

struct progopts opts;

/**
 * print help
 */
void opts_help(char **argv, int exit_status) {
    printf("Shadow Recruit's CPU Scheduling Simulator:\n"
           "Usage: %s [OPTION ...] INPUT_FILE\n"
           "\n"
           "option          default     description\n"
           "======          =======     ===========\n"
           "-t --per_thread disabled    Output additional per thread statistics\n"
           "-v --verbose    disabled    Output information about every state changing\n"
           "                            event and scheduling decision\n"
           "-a --algorithm  FCFS        Algorithm to use: FCFS, RR, PRIORITY, or CUSTOM\n"
           "-h --help                   This message\n",
           argv[0]
      );
    exit(exit_status);
}

/**
 * initialize opts from argc and argv
 */
void opts_init(int argc, char **argv) {
    opts = (struct progopts){.per_thread=false, .verbose=false, .algo=FCFS};
    const static struct option longopts[] = {
        {"per_thread", no_argument, NULL, 't'},
        {"verbose", no_argument, NULL, 'v'},
        {"algorithm", required_argument, NULL, 'a'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };
    int i, optchar;
    while ((optchar = getopt_long(argc, argv, "tva:h", longopts, &i)) != -1) {
        switch (optchar) {
            case 0:
                break;
            case 't':
                opts.per_thread = true;
                break;
            case 'v':
                opts.verbose = true;
                break;
            case 'a':
                for (int i = 0; i < sizeof(algo_name); i++) {
                    if (!strcmp(optarg, algo_name[i])) {
                        opts.algo = i;
                        goto break_switch;
                    }
                }
                printf("Unknown option for algorithm!\n\n");
            default:
                opts_help(argv, 2);
            case 'h':
                opts_help(argv, 0);
        }
break_switch:
        ;
    }
    if (optind < argc) {
        opts.in_file_name = argv[optind];
    }
    else {
        fprintf(stderr, "INPUT_FILE required!\n\n");
        opts_help(argv, 2);
    }
}
