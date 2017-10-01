#include <stdlib.h>
#include "Process.h"
#include "Thread.h"
#pragma once

enum eventType { 
				THREAD_ARRIVED,
				THREAD_DISPATCH_COMPLETED,
				PROCESS_DISPATCH_COMPLETED,
				CPU_BURST_COMPLETED,
				IO_BURST_COMPLETED,
				THREAD_COMPLETED,
				THREAD_PREEMPTED,
				DISPATCHER_INVOKED
				};

const char* etypes[] = {"THREAD_ARRIVED", "THREAD_DISPATCH_COMLPETED", 
						"PROCESS_DISPATCH_COMPLETED", "CPU_BURST_COMPLETED",
						"IO_BURST_COMPLETED", "THREAD_COMPLETED",
						"THREAD_PREEMPTED", "DISPATCHER_INVOKED"};

struct Event {
	eventType type;
	int time;
	Thread thread;
	Process process;
	int thread_num;
	int process_num;
};

// for use in the priority queue
struct Prioritized {
bool operator()(const Event &lhs, const Event &rhs){
	int t1 = lhs.time;
	int t2 = rhs.time;
	return t1>t2;
	}
};
