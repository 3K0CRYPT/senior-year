#include <stdlib.h>
#include "Thread.h"
#include <vector>
#pragma once

enum priorityState {SYSTEM = 0, INTERACTIVE = 1, NORMAL = 2, BATCH = 3}; // for prioritizing
const char* ptypes[] = {"SYSTEM", "INTERACTIVE", "NORMAL", "BATCH"};

struct Process {
	priorityState type;
	int inttype;
	int pid;
	int num_threads;
	std::vector<Thread> threads; // hold pointers instead of copies
};
