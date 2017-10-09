#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <getopt.h>
#include <vector>
#include <string>
#include "info/process.h"
#include "info/thread.h"
#include "info/event.h"
#include "info/burst.h"
#include "info/helpers.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;

int num_processes, thread_switch_overhead, process_switch_overhead;
int num_threads = 0;
int completed_threads = 0;

// Boolean flags for the user's options
bool per_thread_mode = false;
bool verbose_mode = false;

// Enum to track which algorithm to use- default to FCFS
algorithm selected_algorithm = FCFS;

int current_time = 0; 
queue<Thread> ready_queue;
vector<Thread> blocked_threads;
Thread running_thread;
int previous_process_id = -10000;
Thread dummy_thread;

struct less_than {  
   bool operator()(const Event& l, const Event& r) {  
       return l.time > r.time;  
   }  
 };  


void printEvents(priority_queue<Event, vector<Event>, less_than> event_queue) {
	while (!event_queue.empty()) {
		Event current_event = event_queue.top();
		cout << "At time " << current_event.time << ":" << endl;
		string event_type;
		switch(current_event.event_type)  {
			case 0:
			event_type = "THREAD_ARRIVED";
			break;

			case 1:
			event_type = "THREAD_DISPATCH_COMPLETED";
			break;

			case 2:
			event_type = "PROCESS_DISPATCH_COMPLETED";
			break;

			case 3:
			event_type = "CPU_BURST_COMPLETED";
			break;

			case 4:
			event_type = "IO_BURST_COMPLETED";
			break;

			case 5:
			event_type = "THREAD_COMPLETED";
			break;

			case 6:
			event_type = "THREAD_PREEMPTED";
			break;

			case 7:
			event_type = "DISPATCHER_INVOKED";
			break;
		}

		cout << event_type << endl;
		string process_type; 
		switch(current_event.process.type)  {
			case 0:
			process_type = "SYSTEM";
			break;
			case 1:
			process_type = "INTERACTIVE";
			break;
			case 2:
			process_type = "NORMAL";
			break;
			case 3:
			process_type = "BATCH";
			break;
		}
		cout << "Thread " << current_event.thread.thread_number << " in process " << current_event.process.pid;
		cout << " [" << process_type << "]" << endl;
		cout << "Thread arrived." << endl << endl; 
		event_queue.pop();
	}
} 

/*
priority_queue<Event, vector<Event>, less_than> createEvents(vector<Process> processes) {
	priority_queue<Event, vector<Event>, less_than> event_queue;
	for (int i = 0; i < processes.size(); i++) {
		for (int j = 0; j < processes[i].threads.size(); j++) {
			Event current_event;
			current_event.time = processes[i].threads[j].arrival_time;
			current_event.event_type = Event::Event_Type::THREAD_ARRIVED;
			current_event.process = processes[i];
			current_event.process_number = i;
			current_event.thread = processes[i].threads[j];
			current_event.thread_number = j;
			event_queue.push(current_event);
		}
	}
	return event_queue;
}  */


priority_queue<Event, vector<Event>, less_than> switch_threads(vector<Process> processes, priority_queue<Event, vector<Event>, less_than> event_queue ) {
	// Make event for invoking dispatcher
	Event new_event;
	
	if (!ready_queue.empty()) {
	 	running_thread = ready_queue.front();
		ready_queue.pop();

		// while (running_thread.bursts.empty()) {
		// 	running_thread = ready_queue.front();
		// 	ready_queue.pop();
		// }

		new_event.time = current_time;
		new_event.event_type = Event::Event_Type::DISPATCHER_INVOKED;
		new_event.thread = running_thread;
		new_event.process = processes[running_thread.parent_process_id];
		event_queue.push(new_event);

		// Make event for dispatch completing
		new_event.time = current_time;
		new_event.thread = running_thread;
		new_event.process = processes[running_thread.parent_process_id];
		event_queue.push(new_event);

		// If same process as last thread, just dispatch threads
		if (running_thread.parent_process_id == previous_process_id) {
			new_event.event_type = Event::Event_Type::THREAD_DISPATCH_COMPLETED;
		}
		
		// If switch processes, make it a process dispatch event
		else {
			new_event.event_type = Event::Event_Type::PROCESS_DISPATCH_COMPLETED;
		}
	}

	else {
		running_thread = dummy_thread;
	}
	
	return event_queue;
}

priority_queue<Event, vector<Event>, less_than> fcfsAlgorithm(vector<Process> processes) {
	priority_queue<Event, vector<Event>, less_than> event_queue;
	
	// Iterate through all of the threads in all of the processes and 
	// check if any threads arrive at time 0. If so, add event to the event queue
	// and add thread to ready queue.
	for (int i = 0; i < processes.size(); i++) {
		for (int j = 0; j < processes[i].threads.size(); j++) {
			Thread current_thread = processes[i].threads[j];
			if (current_thread.arrival_time == 0) {
				Event current_event;
				current_event.time = current_thread.arrival_time;
				current_event.event_type = Event::Event_Type::THREAD_ARRIVED;
				current_event.process = processes[i];
				//current_event.process_number = i;
				current_event.thread = processes[i].threads[j];
				event_queue.push(current_event);
				ready_queue.push(current_thread);
				//printf("Adding P[%d]T[%d] to ready queue\n", current_thread.parent_process_id, current_thread.thread_number);
			}
		}
	}


	running_thread = ready_queue.front();
	ready_queue.pop();

	while (completed_threads != num_threads) {
		//printf("Current time: %d\n", current_time);
		//printf("Running thread: P[%d]T[%d]\n", running_thread.parent_process_id, running_thread.thread_number);
		//printf("Events: %lu\n", event_queue.size());
		// Iterate through all of the threads in all of the processes and 
		// check if any threads arrival at the current time. If so, add event to the event queue
		// and add thread to ready queue.
		for (int i = 0; i < processes.size(); i++) {
			for (int j = 0; j < processes[i].threads.size(); j++) {
				Thread current_thread = processes[i].threads[j];
				if (current_thread.arrival_time == current_time && current_time != 0) {
					Event current_event;
					current_event.time = current_thread.arrival_time;
					current_event.event_type = Event::Event_Type::THREAD_ARRIVED;
					current_event.process = processes[i];
					//current_event.process_number = i;
					current_event.thread = processes[i].threads[j];
					event_queue.push(current_event);
					ready_queue.push(current_thread);
					//printf("Adding P[%d]T[%d] to ready queue\n", current_thread.parent_process_id, current_thread.thread_number);
				}
			}
		}

		vector<int> indices_to_remove;
		// Run through all blocked processes and check if any completed their IO burst (now ready)
		for (int i = 0; i < blocked_threads.size(); i++) {
			Thread current_thread = blocked_threads[i];
			//if (current_thread.bursts[current_thread.current_burst].remaining_time == 0) {
			if (current_thread.bursts.front().remaining_time == 0) {
				//printf("Thread no longer blocked\n");
				// Add thread to ready queue
				//current_thread.bursts.erase(current_thread.bursts.begin());
				//current_thread.current_burst++;
				current_thread.bursts.pop();
				ready_queue.push(current_thread);
				//printf("Adding P[%d]T[%d] to ready queue\n", current_thread.parent_process_id, current_thread.thread_number);
				indices_to_remove.push_back(i);
			}		
			//printf("Indices to remove: %lu\n", indices_to_remove.size());
		}

		for (int i = 0; i < indices_to_remove.size(); i++) {
			// Remove thread from blocked vector
			blocked_threads.erase(blocked_threads.begin() + indices_to_remove[i]); 
		}
		indices_to_remove.clear();

		// Check if running thread's current burst is over
		//if (running_thread.bursts[running_thread.current_burst].remaining_time == 0) {
		if (running_thread.thread_number > -1 && running_thread.bursts.front().remaining_time == 0) {
			//printf("Burst finished!\n");
			Event new_event;
			new_event.time = current_time;
			new_event.thread = running_thread;
			new_event.process = processes[running_thread.parent_process_id];

			// If CPU burst just finished, make event and move thread to blocked vector
			//if (running_thread.bursts[0].type == Burst::CPU) {
				new_event.event_type = Event::Event_Type::CPU_BURST_COMPLETED;
				//printf("CPU burst done, Waiting on IO\n");
				//printf("We here\n");
				
				// Remove the completed burst from the thread
				//running_thread.bursts.erase(running_thread.bursts.begin());
				//running_thread.current_burst++;
				running_thread.bursts.pop();

				// Check if running thread is completed (no more bursts)
				// Make event and invoke dispatcher to get next thread
				if (running_thread.bursts.empty()) {	
				//if (running_thread.current_burst >= running_thread.bursts.size()) {
					// Make event for the thread completion
					new_event.time = current_time;
					new_event.event_type = Event::Event_Type::THREAD_COMPLETED;
					new_event.thread = running_thread;
					new_event.process = processes[running_thread.parent_process_id];
					event_queue.push(new_event);
					completed_threads++;
					//printf("Completed a thread\n");



					// Set previous process id value for checking the context switch
					previous_process_id = running_thread.parent_process_id;
				}
				
				// If thread isn't completed, it is blocked (waiting on IO burst)
				else {
					// Move thread that was running to blocked vector
					blocked_threads.push_back(running_thread);
				}

				// Switch to new thread
				event_queue = switch_threads(processes, event_queue);
				//printf("New running thread: P[%d]T[%d]\n", running_thread.parent_process_id, running_thread.thread_number);
				//printf("\nRunning thread number of bursts: %lu\n\n", running_thread.bursts.size());
			
			//}

			// // If IO burst just finished, make event and move thread from blocked vector to ready queue
			// else {
			// 	new_event.event_type = Event::Event_Type::IO_BURST_COMPLETED;
			// 	ready_queue.push(running_thread);
			// 	printf("We hittin dis?");
			// }

		}

		else if (running_thread.thread_number < 0 && !ready_queue.empty()) {
			event_queue = switch_threads(processes, event_queue);
			//printf("New running thread: P[%d]T[%d]\n", running_thread.parent_process_id, running_thread.thread_number);
			//printf("\nRunning thread number of bursts: %lu\n\n", running_thread.bursts.size());
		} 

		// Decrement remaining time on running thread's CPU burst
		if (running_thread.thread_number >-1) {
			running_thread.bursts.front().remaining_time--;
		}
		// Run through all blocked processes and decrement the remaining time on their IO burst
		for (int i = 0; i < blocked_threads.size(); i++) {
			blocked_threads[i].bursts.front().remaining_time--;	
		}

		current_time++;
		//printf("Time remaining on burst: %d\n", running_thread.bursts[running_thread.current_burst].remaining_time);
		//printf("Burst type: %d\n", running_thread.bursts[running_thread.current_burst].type);
		//printf("\n");

		// if (running_thread.bursts.front().remaining_time < 0) {
		// 	exit(EXIT_FAILURE);
		// }

		//printf("Ready Queue size: %lu\n", ready_queue.size());
	}


	return event_queue;
}

void rrAlgorithm(vector<Process> processes) {
	
}

void priorityAlgorithm(vector<Process> processes) {
	
}

void customAlgorithm(vector<Process> processes) {
	
}

int main(int argc, char *argv[]) {
	string file;
	priority_queue<Event, vector<Event>, less_than> event_queue;
	dummy_thread.thread_number = -10000;

	processArguments(argc, argv);
	//printf("YO");

	if (argv[1] != NULL) {
		file = argv[optind];
	}

	vector<Process> processes = readFile(file);
	//printf("%lu\n", processes.size());


	switch(selected_algorithm) {
		case 0: // FCFS
		event_queue = fcfsAlgorithm(processes);
		break;

		case 1: //RR
		rrAlgorithm(processes);
		break;

		case 2: // PRIORITY
		priorityAlgorithm(processes);
		break;

		case 3: // CUSTOM
		customAlgorithm(processes);
		break;

		default:
		break;
	}

	//priority_queue<Event, vector<Event>, less_than> event_queue = createEvents(processes);

	//printf("%d", event_queue.size());
	printEvents(event_queue);

	return 0;
}