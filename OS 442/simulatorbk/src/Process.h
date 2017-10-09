#include <vector>
#include "Thread.h"
#pragma once

enum priorityState {
	SYSTEM = 0,
	INTERACTIVE = 1,
	NORMAL = 2,
	BATCH = 3
};

const char* priorityState_str[] = {
	"SYSTEM",
	"INTERACTIVE",
	"NORMAL",
	"BATCH"
};

struct Process {
	priorityState state;
	int inttype, processID, threadQuantity;
	std::vector<Thread> threads;
};
