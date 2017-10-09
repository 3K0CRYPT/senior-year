#pragma once
#include <vector>
#include "burst.h"
#include "process.h"
#include <queue>

using namespace std;

struct Thread {
	enum Thread_State {NEW, READY, RUNNING, BLOCKED, EXIT};

	int thread_number;

	int arrival_time;

	int num_CPU_bursts;

	Thread_State state;

	int parent_process_id;
	
	//vector<Burst> bursts;

	//int current_burst = 0;

	queue<Burst> bursts;
};
