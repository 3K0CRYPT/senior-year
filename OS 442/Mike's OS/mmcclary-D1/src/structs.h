#ifndef STRUCTS_H_INCLUDE
#define STRUCTS_H_INCLUE
#include<stdlib.h>
using namespace std;


struct Burst{
int cpuTime;
int ioTime = 0;
};

struct Thread{
enum ThreadState {NEW, READY, RUNNING, BLOCKED, EXIT};
ThreadState ts;
int arrivalTime;
int numBursts;
vector <Burst> bursts;
};

struct Process{
enum ProcType {SYSTEM = 0, INTERACTIVE = 1, NORMAL = 2, BATCH = 3};
ProcType pt;
int processNumber;
int numThreads;
vector<Thread> threads;
};

struct Event{
enum EventType {THREAD_ARRIVED, THREAD_DISPATCH_COMPLETED, PROCESS_DISPATCH_COMPLETED, CPU_BURST_COMPLETED, IO_BURST_COMPLETED,
		THREAD_COMPLETED, THREAD_PREEMPTED, DISPATCHER_INVOKED};
int time;
EventType et;
Thread t;
int threadNumber;
Process p;
int processNumber;
};

struct LowerArrivalTime{
bool operator()(const Event &lhs, const Event &rhs){
	int t1 = lhs.time;
	int t2 = rhs.time;
	return t1>t2;
	}
};

#endif
