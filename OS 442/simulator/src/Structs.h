#pragma once
#include <vector>


enum burstType {CPU, IO};

const char* burstType_str[] = {"CPU", "IO"};

struct Burst {
	burstType type;
	int cpuTime;
	int ioTime;
};

enum threadState { 
	NEW,
	READY,
	RUNNING,
	BLOCKED,
	EXIT
};

const char* threadState_str[] = {
	"NEW",
	"READY",
	"RUNNIMG",
	"BLOCKED",
	"EXIT"
};

struct Thread {
	int offset, burstQuantity, arriveTime, beginTime, finishTime, serveTime, cpuTime, ioTime, lastTime, lastBlock;
	threadState current, last;
	std::vector<Burst> bursts;

	void setReady(),  setRunning(),  setBlocked(),  setExit();

};

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
