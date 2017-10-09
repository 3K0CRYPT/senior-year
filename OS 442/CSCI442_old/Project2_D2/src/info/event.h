#pragma once
#include "thread.h"
#include "process.h"

struct Event {
	enum Event_Type {THREAD_ARRIVED, THREAD_DISPATCH_COMPLETED, PROCESS_DISPATCH_COMPLETED, 
		CPU_BURST_COMPLETED, IO_BURST_COMPLETED, THREAD_COMPLETED, THREAD_PREEMPTED, 
		DISPATCHER_INVOKED};

	int time; 

	Thread thread;

	//int thread_number;

	Process process; 

	//int process_number;

	Event_Type event_type;
};