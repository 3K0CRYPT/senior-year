#include "Process.h"
#include "Thread.h"
#pragma once

enum eventType { 
	THREAD_ARRIVED,
	THREAD_DISPATCH_COMLPETED,
	PROCESS_DISPATCH_COMPLETED,
	CPU_BURST_COMPLETED,
	IO_BURST_COMPLETED,
	THREAD_COMPLETED,
	THREAD_PREEMPTED,
	DISPATCHER_INVOKED
};

const char* eventType_str[] = {
	"THREAD_ARRIVED",
	"THREAD_DISPATCH_COMLPETED",
	"PROCESS_DISPATCH_COMPLETED",
	"CPU_BURST_COMPLETED",
	"IO_BURST_COMPLETED",
	"THREAD_COMPLETED",
	"THREAD_PREEMPTED",
	"DISPATCHER_INVOKED"
};

struct Event {
	eventType type;
	Thread thread;
	Process process;
	int time, threadNum, processNum;
};

struct Prioritized {
	bool operator()(const Event &event1, const Event &event2){ return event1.time>event2.time; }
};
