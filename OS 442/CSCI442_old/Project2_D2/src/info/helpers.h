#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <getopt.h>
#include "process.h"

enum algorithm {FCFS, RR, PRIORITY, CUSTOM};

extern int num_processes, thread_switch_overhead, process_switch_overhead, num_threads;
extern bool per_thread_mode, verbose_mode;
extern algorithm selected_algorithm;

vector<Process> readFile(string fileName);

void printHelp();

void processArguments(int argc, char** argv);