#include "Burst.h"
#include <vector>
#pragma once

enum threadType {NEW, READY, RUNNING, BLOCKED, EXIT};
const char* ttypes[] = {"NEW", "READY", "RUNNIMG", "BLOCKED", "EXIT"};

struct Thread {
	threadType current, last;
	// struct process parent_process;
	std::vector<Burst> bursts;
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

	void setReady();
	void setRunning();
	void setBlocked();
	void setExit();

};
