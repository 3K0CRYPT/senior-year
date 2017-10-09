#include "Burst.h"
#include <vector>
#pragma once

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

	void setReady();
	void setRunning();
	void setBlocked();
	void setExit();

};
