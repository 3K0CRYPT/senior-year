#include <iostream>
#include <fstream>
#include <sstream>
#include "Process.h"
#include "Event.h"
#include "Burst.h"
#include "Thread.h"
#include <getopt.h>
#include <vector>
#include <queue>
//#include <string>

#define no_argument 0 // must be defined for getopt
#define required_argument 1 // ""
#define optional_argument 2 // ""

using namespace std;

string infilename;
int num_processes;
int thread_switch_overhead;
int process_switch_overhead;
priority_queue <Event, vector<Event>, Prioritized> theQueue; 


void processArgs(int argc, char** argv);

int main(int argc, char* argv[]) {
  processArgs(argc, argv);
  // cout << "args processed" << endl;
  // infilename should how hold file, time to comb through it
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
  		stringstream sss(line);
  		// cout << "line" << line << endl;
  		sss >> thread.arrivalTime >> thread.numBursts;
  		// We gotta go deeper
  		// last CPU burst doesn't have IO, so go up to second to last in input file
  		for(int k = 0; k < thread.numBursts - 1; k++) {
  			Burst burst;
  			getline(infile, line);
  			stringstream ssss(line);
  			ssss >> burst.cpuTime >> burst.ioTime;
  			// could have also used my constructor
  			thread.bursts.push_back(burst);
  		}
  		Burst lastburst;
  		getline(infile, line);
  		stringstream lastss(line);
  		lastss >> lastburst.cpuTime;
  		thread.bursts.push_back(lastburst);
  		process.threads.push_back(thread);
  	}
  	processes.push_back(process);
  }
  infile.close();
  for(int i = 0; i < processes.size(); i++) {
  	for(int j = 0; j < processes[i].num_threads; j++) {
  		Event event;
  		event.time = processes[i].threads[j].arrivalTime;
  		event.type = eventType::THREAD_ARRIVED; // threads have only arrived at this point
  		event.thread = processes[i].threads[j];
  		event.process = processes[i];
  		event.thread_num = j;
  		event.process_num = i;
  		theQueue.push(event);
  	}
  }

  // Poop em all back out.
  cout << "------------ALL EVENTS-------------" << endl;
  while(!theQueue.empty()) {
  	string eTypeString;
  	string pTypeString;
  	Event event = theQueue.top();
  	// MAKE NOT HARD CODED LATER
  	eTypeString = "THREAD_ARRIVED";
  	switch(event.process.type) {
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
  	cout << "TIME: " << event.time << endl;
  	cout << "TYPE: " << eTypeString << endl;
  	cout << "PROCESS TYPE: " << pTypeString << endl;
  	cout << "Thread " << event.thread_num << " in process " << event.process_num << endl;
  	cout << endl << endl;
  	theQueue.pop();
  }

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
  //int val = 0; // will get val from arguments;
  int opt = 0;
  while((opt = getopt_long(argc, argv, short_flag, long_flag, NULL)) != -1) {
  	cout << "Getting arguments" << endl;
  	cout << "opt is " << opt << endl;

    if(opt == -1) {
    	cout << "No arguments" << endl;
      // no arguments
      break;
    }
    switch(opt) {
      case 't':
        cout << "Flag t" << endl;
      	printf(infilename.c_str());
        cout << endl;
        break;
      case 'v':
        cout << "Flag v" << endl;
      	printf(infilename.c_str());
        cout << endl;
        break;
      case 'a':
        cout << "Flag a" << endl;
      	printf(infilename.c_str());
        cout << endl;
        break;
      case 'h':
        cout << "Flag h" << endl;
      	printf(infilename.c_str());
        cout << endl;
        break;
      default:
      	//strcpy(infilename, optarg);
      	// JUST PRINT THE HELP THING
      	cout << "Default case" << endl;
      	printf(infilename.c_str());
      	break;
    }
  }
}
