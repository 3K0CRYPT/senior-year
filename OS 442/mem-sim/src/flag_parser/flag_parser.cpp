/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
const char* const short_options = "v::s:f:h";
const option long_options[] = { {"verbose", no_argument, 0, 'v'}, {"strategy", required_argument, 0, 's'}, {"max-frames", required_argument, 0, 'f'}, {"help", no_argument, 0, 'h'} };

int option_int = 0, opt; bool noError = true;

while(true) {
        opt = getopt_long(argc, argv, short_options, long_options, &option_int);
        if (opt == -1) break;
        switch (opt) {
                case '?':
                        noError = false;
                        break;
                case 'v':
                        flags.verbose = true;
                        break;
                case 's':
                        string strat;
                        strat = argv[optind-1];

                        if(strat == "LRU") flags.strategy = ReplacementStrategy::LRU;
                        else if (strat == "FIFO") flags.strategy = ReplacementStrategy::FIFO;
                        else noError=false;
                        break;
                case 'f':
                        int maxFrames= atoi(argv[optind-1]);
                        if (maxFrames <= 0) noError = false;
                        else flags.max_frames = maxFrames;
                        break;
                case 'h':
                default:
                print_usage(); 
                break;
        }
}

if(argv[1] != NULL) flags.filename = argv[argc-1];
else noError = false;
return noError;

}

