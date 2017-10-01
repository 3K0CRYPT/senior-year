#include "Burst.h"
#include <queue>
#include <iostream>
#pragma once

enum threadType {NEW, READY, RUNNING, BLOCKED, EXIT};
const char* ttypes[] = {"NEW", "READY", "RUNNIMG", "BLOCKED", "EXIT"};

struct Thread {
	threadType type;
	// struct process parent_process;
	std::queue<Burst> bursts;
	int threadNumber;
	int offset;
	int numBursts;
	int arrivalTime;
	int startTime;
	int endTime;
	int serviceTime;
	int cpuTime;
	int ioTime;
	int lastTime;
	int lastBlock;
	int parentPID;

	void setReady();
	void setRunning();
	void setBlocked();
	void setExit();

};
