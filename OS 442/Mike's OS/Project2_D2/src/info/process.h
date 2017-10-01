#pragma once
#include <vector>
#include "thread.h"

using namespace std;

struct Process {
	enum Process_Type {SYSTEM = 0, INTERACTIVE = 1, NORMAL = 2, BATCH = 3};

	int pid;

	Process_Type type;

	int num_threads; 

	vector<Thread> threads;

};