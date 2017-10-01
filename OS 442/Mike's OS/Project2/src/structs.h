#ifndef STRUCTS_H_INCLUDE
#define STRUCTS_H_INCLUE
#include<stdlib.h>
using namespace std;


struct Burst{
enum BurstType {CPU,IO};
BurstType type;
int totalTime;
int remainingTime;
};

struct Thread{
enum ThreadState {NEW, READY, RUNNING, BLOCKED, EXIT};
ThreadState ts;
int threadNum;
int arrivalTime;
int numBursts;
int parentId;
vector <Burst> bursts;
};

struct Process{
enum ProcType {SYSTEM = 0, INTERACTIVE = 1, NORMAL = 2, BATCH = 3};
ProcType pt;
int processId;
int numThreads;
vector<Thread> threads;
};

struct Event{
enum EventType {THREAD_ARRIVED, THREAD_DISPATCH_COMPLETED, PROCESS_DISPATCH_COMPLETED, CPU_BURST_COMPLETED, IO_BURST_COMPLETED,
		THREAD_COMPLETED, THREAD_PREEMPTED, DISPATCHER_INVOKED};
int time;
EventType et;
Thread t;
Process p;
};

struct Metrics{
	int threadOverhead, processOverhead;
	struct sysThreads{
		int numThreads =0;
		int art =0, att=0;
	};
	sysThreads st;
	struct intThreads{
		int numThreads=0;
		int art=0, att=0;
	};
	intThreads it;
	struct normThreads{
		int numThreads=0;
		int art=0, att=0;
	};
	normThreads nt;
	struct batchThreads{
		int numThreads=0;
		int art=0, att=0;
	};
	batchThreads bt;
int totalTime=0,serviceTime=0, ioTime=0, overhead=0,CPUIdle=0;
double CPUUtil=0, CPUEffic=0;
};


struct LowerArrivalTime{
bool operator()(const Event &lhs, const Event &rhs){
	int t1 = lhs.time;
	int t2 = rhs.time;
	return t1>t2;
	}
};

#endif
