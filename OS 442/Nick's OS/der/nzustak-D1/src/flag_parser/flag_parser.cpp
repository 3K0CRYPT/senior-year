/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

 #include "flag_parser/flag_parser.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <getopt.h>
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
  // TODO: implement me
  // FlagOptions will hold the flag options. Fancy. That
  const char* const short_flag = "vs:f:h";
  const static struct option lopts[] {
      {"verbose", no_argument, NULL, 'v'},
      {"strategy", required_argument, NULL, 's'},
      {"max-frames", required_argument, NULL, 'f'},
      {"help", no_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}
    };

  // Default strategy is FIFO
    flags.strategy = ReplacementStrategy::FIFO;
    // looks like that's already set in the header whatever

  int opt, whatever = 0;
  int fdup = 0; // if even one thing goes wrong, this goes positive
                // will return !fdup to make sure nothing went wrong

  while((opt = getopt_long(argc, argv, short_flag, lopts, &whatever)) != -1) {
      switch (opt) {
          case 0:
              break; // no flags, do nothing
          case 'v':
              flags.verbose = true;
              break;
          case 's':
              // see what type of strategy is set
              // strcmp returns 0 if the two passed strings are the same
              if(!strcmp(optarg, "FIFO"))
                  flags.strategy = ReplacementStrategy::FIFO;
              else if(!strcmp(optarg, "LRU"))
                  flags.strategy = ReplacementStrategy::LRU;
              else fdup++; // add 1 to the fk'd up counter
              break;
          case 'f':
              // One line of code to add the max frames from the argument
              // And to break us if improperly formatted
              fdup += !sscanf(optarg, "%d", &flags.max_frames); // must be passed by ref
              if (flags.max_frames < 1)
                  fdup++;
              break;
          case 'h':
              print_usage();
              exit(0);
          default:
              cout << "Must provide an argument. Exiting..." << endl;
              fdup++;
      }
  }

  // Filename will be last argument
  // Scan through to find it
  //
  while (optind < argc - 1) {
      optind++;
  }
  if (optind < argc)
      flags.filename = argv[optind];
  else fdup++; // there was no filename.

  if(fdup) {
    cout << "Parsing broke in " << fdup << " places." << endl;
  }
  return !fdup;
}
