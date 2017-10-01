#include <fstream>
#include <sstream>
#include "Process.h"
#include "Event.h"
#include "Burst.h"
#include "Thread.h"
#include <getopt.h>
#include <vector>
#include <queue>
#include <ncurses.h>
#include <iostream>

//#include <string>

#define no_argument 0 // must be defined for getopt
#define required_argument 1 // ""
#define optional_argument 2 // ""

using namespace std;

enum algorithm {FCFS, RR, PRIORITY, CUSTOM};

string infilename;
int num_processes;
int thread_switch_overhead;
int process_switch_overhead;
int num_threads;
int finished_threads;
int currentTime;

bool per_thread;
bool verbose;
algorithm current_algorithm = FCFS;

Thread current_thread;
Thread temp;
vector<Thread> blocked;
int prevPID = -1;

vector<Process> processes;
priority_queue <Event, vector<Event>, Prioritized> theQueue; 
queue<Thread> rdyQueue;


void processArgs(int argc, char** argv);
void onHelp();
vector<Process> fillProcesses(string infilename);
priority_queue<Event, vector<Event>, Prioritized> FCFSAlgo();
void eventLog();

int main(int argc, char* argv[]) {
  processArgs(argc, argv);
  // cout << "args processed" << endl;
  // infilename should how hold file, time to comb through it
  // Algorithm selected
  processes = fillProcesses(infilename);
  temp.threadNumber = -1; // for testing

  cout << "Filled processes" << endl;

  switch(current_algorithm) {
    case 0: // FCFS
    cout << "Attempting FCFS" << endl;
    theQueue = FCFSAlgo();
    break;

    case 1: 
    // implement RR
    break;

    case 2: 
    // implement PRIORITY
    break;

    case 3: 
    // implement CUSTOM
    break;

    default:
    break;
  }

  // Print everything
  cout << "Attempting to print" << endl;
  eventLog();

  return 0;
}

void processArgs(int argc, char* argv[]) {
  // Will use getopt to ensure proper number of flags are used, if at all
  // Sends errors / help screen if otherwise
  const char* const short_flag = "tva:h";
  // option constructor (name, has_arg, flag, val), if flag ==0, then val is a unique int describing the option.
  // In this case, an int in the form of a char
  const option long_flag[] = {{"per_thread", no_argument, 0, 't'},
                              {"verbose", no_argument, 0, 'v'},
                              {"algorithm", no_argument, 0, 'a'},
                              {"help", no_argument, 0, 'h'},
                              {0,0,0,0}};
  infilename = argv[argc-1];
  int opt = 0;
  string algo = "FCFS";
  while((opt = getopt_long(argc, argv, short_flag, long_flag, NULL)) != -1) {
  	cout << "Getting arguments" << endl;
  	cout << "opt is " << opt << endl;

    if(opt == -1) {
    	cout << "No arguments" << endl;
      break;
    }
    switch(opt) {
      case 't':
        cout << "Flag t" << endl;
      	per_thread = true;
        cout << endl;
        break;
      case 'v':
        cout << "Flag v" << endl;
      	verbose = true;
        cout << endl;
        break;
      case 'a':
        printf("Algorithm flag selected\n");
        algo = argv[optind-1];

        if (algo == "FCFS") {
          current_algorithm = FCFS;
        }

        else if (algo == "RR") {
          current_algorithm = RR;
        }

        else if (algo == "PRIORITY") {
          current_algorithm = PRIORITY;
        }

        else if (algo == "CUSTOM") {
          current_algorithm = CUSTOM;
        }
      
        else {
          printf("Invalid algorithm, exiting.\n");
          endwin();
          exit(EXIT_SUCCESS);
        }
        break;
      case 'h':
        cout << "Flag h" << endl;
        onHelp();
        cout << endl;
        break;
      default:
      	//strcpy(infilename, optarg);
      	// JUST PRINT THE HELP THING
      	onHelp();
        cout << endl;
      	break;
    }
  }
}

vector<Process> fillProcesses(string infilename) {
  ifstream infile(infilename);

  if(!infile.is_open()) {
    cerr << "Couldn't open: " << infilename << endl;
  }

  vector<Process> processes;

  // Grab everything we need from the file
  infile >> num_processes >> thread_switch_overhead >> process_switch_overhead;
  string line, temp; // holder strings
  // All the processes
  for(int i = 0; i < num_processes; i++) {
    Process process;
    processType pType;
    getline(infile, line);
    if(line.empty()) {
      while(line.empty() | infile.eof()) {
        // ignore empty lines
        //cout << "1st Empty line!" << endl;
      getline(infile, line);
      }
    }
    stringstream ss(line);
    int process_type;
    ss >> process.pid >> process.inttype >> process.num_threads;
    num_threads += process.num_threads;
    // This is the only obvious way to cast to enum
    process.type = static_cast<processType>(process.inttype); // well and contained inside this process
    for(int j = 0; j < process.num_threads; j++) {
      getline(infile, line);
      if(line.empty()) {
        while(line.empty() | infile.eof()) {
          // ignore empty lines
          // cout << "1st Empty line!" << endl;
        getline(infile, line);
        }
      }
      Thread thread;
      thread.parentPID = process.pid;
      stringstream sss(line);
      // cout << "line" << line << endl;
      sss >> thread.arrivalTime >> thread.numBursts;
      thread.type = threadType::NEW;
      thread.threadNumber = j;
      // We gotta go deeper
      // last CPU burst doesn't have IO, so go up to second to last in input file
      for(int k = 0; k < thread.numBursts - 1; k++) {
        Burst burstCPU;
        Burst burstIO;
        getline(infile, line);
        stringstream ssss(line);
        ssss >> burstCPU.time >> burstIO.time;
        burstCPU.remainingTime = burstCPU.time;
        burstIO.remainingTime = burstCPU.time;
        burstCPU.type = burstType::CPU;
        burstIO.type = burstType::IO;
        // could have also used my constructor
        thread.bursts.push(burstCPU);
        thread.bursts.push(burstIO);

      }
      Burst lastburst;
      getline(infile, line);
      stringstream lastss(line);
      lastss >> lastburst.time;
      lastburst.remainingTime = lastburst.time;
      lastburst.type = burstType::CPU;
      thread.bursts.push(lastburst);
      process.threads.push_back(thread);
    }
    processes.push_back(process);
    cout << "Process pushed back" << endl;
    cout << "Number of processes: " << processes.size() << endl;
  }
  infile.close();

  return processes;
}

priority_queue<Event, vector<Event>, Prioritized> swap(priority_queue<Event, vector<Event>, Prioritized> event_queue ) {
  
  Event dispatchEvent;
  
  if (!rdyQueue.empty()) {
    current_thread = rdyQueue.front();
    rdyQueue.pop();

    // Dispatcher invoked
    dispatchEvent.time = currentTime;
    dispatchEvent.type = eventType::DISPATCHER_INVOKED;
    dispatchEvent.thread = current_thread;
    dispatchEvent.process = processes[current_thread.parentPID];
    event_queue.push(dispatchEvent);

    // Dispatcher completed 
    dispatchEvent.time = currentTime;
    dispatchEvent.thread = current_thread;
    dispatchEvent.process = processes[current_thread.parentPID];
    event_queue.push(dispatchEvent);

    // Noo need to swap
    if (current_thread.parentPID == prevPID) {
      dispatchEvent.type = eventType::THREAD_DISPATCH_COMPLETED;
    }
    
    // Gotta swhauap
    else {
      dispatchEvent.type = eventType::PROCESS_DISPATCH_COMPLETED;
    }

    event_queue.push(dispatchEvent);

  }

  else {
    current_thread = temp;
  }
  
  return event_queue;
}

priority_queue<Event, vector<Event>, Prioritized> FCFSAlgo() {
  priority_queue<Event, vector<Event>, Prioritized> the_queue;

  // check for arriving threads
  cout << "Finding arriving threads" << endl;
  cout << "Num processes: " << processes.size() << endl;
  for(int i = 0; i < processes.size(); i++) {
    for(int j = 0; j < processes[i].num_threads; j++) {
      cout << "Process " << i << " num threads: " << processes[i].num_threads << endl;
      Thread currentt = processes[i].threads[j];
      cout << "Current thread arrivalTime" << current_thread.arrivalTime << endl;
      if (current_thread.arrivalTime == 0) {
        Event event;
        event.time = processes[i].threads[j].arrivalTime;
        event.type = eventType::THREAD_ARRIVED; // threads have only arrived at this point
        event.thread = processes[i].threads[j];
        event.process = processes[i];
        //event.thread_num = j;
        //event.process_num = i;
        the_queue.push(event);
        rdyQueue.push(currentt);
      }
    }
  }

  cout << "Attempting to access ready queue" << endl;

  current_thread = rdyQueue.front();
  rdyQueue.pop();

  while(finished_threads != num_threads) {

    cout << "Attemping to run simulation" << endl;
    cout << "Num_threads = " << num_threads << endl;
    cout << "Finished threads = " << finished_threads << endl;

    for(int i = 0; i < processes.size(); i++) {
      for(int j = 0; j < processes[i].num_threads; j++) {
        Thread currentt = processes[i].threads[j];
        if (current_thread.arrivalTime == currentTime && currentTime != 0) {
          Event event;
          event.time = processes[i].threads[j].arrivalTime;
          event.type = eventType::THREAD_ARRIVED; // threads have only arrived at this point
          event.thread = processes[i].threads[j];
          event.process = processes[i];
          //event.thread_num = j;
          //event.process_num = i;
          the_queue.push(event);
          rdyQueue.push(currentt);
        }
      }
    }

    vector<int> removeFromBlocked;
    cout << "Num blocked threads: " << blocked.size() << endl;
    for( int i = 0; i < blocked.size(); i++) {
      Thread currentt = blocked[i];
      if(currentt.bursts.front().remainingTime == 0) {
          // Get rid of the burst
          currentt.bursts.pop();
          rdyQueue.push(currentt);
          removeFromBlocked.push_back(i); // will remove by index from blocked threads vector
      }
    }

    // Remove from blocked
    for(int i = 0; i < removeFromBlocked.size(); i++) {
      blocked.erase(blocked.begin() + removeFromBlocked[i]);
    }
    removeFromBlocked.clear();

    // Check if we're on the temp thread (number initialized to -1)
    cout << "\n" << current_thread.threadNumber << "threadno"<<endl;
    cout << "Burst remaining time: " << current_thread.bursts.front().remainingTime << endl;
    if( current_thread.bursts.front().remainingTime == 0) {
      if (current_thread.threadNumber == -1)
      {
        return the_queue;
      }
      // Not the temp thead, but burst has completed
          //cout << "nigger\n";
      current_thread.bursts.pop();
      Event event;
      event.time = currentTime;
      event.thread = current_thread;
      event.process = processes[current_thread.parentPID];
      event.type = eventType::CPU_BURST_COMPLETED;

      if(current_thread.bursts.empty()) {
        // if bursts finished, thread completed
        event.time = currentTime;
        event.thread = current_thread;
        event.process = processes[current_thread.parentPID];
        event.type = eventType::THREAD_COMPLETED;
        the_queue.push(event);
        finished_threads++;

        // prepare for switch
        prevPID = current_thread.parentPID;
      }
      else {
        // If bursts aren't finished, thread will move to blocked
        blocked.push_back(current_thread);
      }

      the_queue = swap(the_queue);
    }

    else if (current_thread.threadNumber < 0 && !rdyQueue.empty()) {
      cout << "Dummy thread, and ready queue isn't empty." << endl;
      the_queue = swap(the_queue);
    }

    if(current_thread.threadNumber > -1) {
      current_thread.bursts.front().remainingTime--;
    }

    if(current_thread.threadNumber < 0) {
      cout << "current thread is temp" << endl;
      cout << "current thread bursts remaining time " << current_thread.bursts.front().remainingTime << endl;
      current_thread.bursts.front().remainingTime--;
    }

    currentTime++;

  }

  return the_queue;
}

void eventLog() {
  // Poop em all back out.
  cout << "------------ALL EVENTS-------------" << endl;
  while(!theQueue.empty()) {
    string eTypeString;
    string pTypeString;
    Event top = theQueue.top();
    // MAKE NOT HARD CODED LATER
    int time = top.time;
    cout << "At time " << time << ": " << endl;
    switch(top.type)  {
      case 0:
      eTypeString = "THREAD_ARRIVED";
      break;

      case 1:
      eTypeString = "THREAD_DISPATCH_COMPLETED";
      break;

      case 2:
      eTypeString = "PROCESS_DISPATCH_COMPLETED";
      break;

      case 3:
      eTypeString = "CPU_BURST_COMPLETED";
      break;

      case 4:
      eTypeString = "IO_BURST_COMPLETED";
      break;

      case 5:
      eTypeString = "THREAD_COMPLETED";
      break;

      case 6:
      eTypeString = "THREAD_PREEMPTED";
      break;

      case 7:
      eTypeString = "DISPATCHER_INVOKED";
      break;
    }
    cout << eTypeString << endl;
    switch(top.process.type) {
      case processType::SYSTEM:
        pTypeString = "SYSTEM";
        break;
      case processType::INTERACTIVE:
        pTypeString = "INTERACTIVE";
        break;
      case processType::NORMAL:
        pTypeString = "NORMAL";
        break;
      case processType::BATCH:
        pTypeString = "BATCH";
        break;
    }
    cout << "Thread " << top.thread.threadNumber << " in process " << top.process.pid;
    // cout << "TIME: " << time << endl;
    // cout << "TYPE: " << eTypeString << endl;
    cout << " [" << pTypeString << "] " << endl;
    cout << "Thread arrived.";
    cout << endl << endl;
    theQueue.pop();
  }
}

void onHelp(){
  printf("\r\n/////// Help Screen ///////");
  printf("\r\n-h or --help will show this, the help screen");
  printf("\r\n-t or --per_thread will show more information on each thread");
  printf("\r\n-v or --verbose will show information on every state changing decision");
  printf("\r\n-a or --algoirthm [ALGORITHM] will change the scheduling algorithm. Default is FCFS");
  printf("\r\n\t FCFS - first come, first serve scheduling");
  printf("\r\n\t RR - round robin scheduling");
  printf("\r\n\t PRIORITY - round robin scheduling with priority\n\t in dec. order SYSTEM, INTERACTIVE, NORMAL, BATCH");
  printf("\r\n\t CUSTOM - Nick's Custom Algorithm, served with grits\n");
  endwin();
  exit(EXIT_SUCCESS);
}
