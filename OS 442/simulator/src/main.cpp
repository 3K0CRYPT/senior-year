#include "includes.h"

#define argNone 0 
#define argReq 1 
#define argOpt 2 

using namespace std;

void argHandler(int argc, char** argv);

string fileName;
int processQuantity, switchOverhead_thread, switchOverhead_process;
priority_queue <Event, vector<Event>, Prioritized> PQ; 

int main(int argc, char* argv[]) {
  argHandler(argc, argv);

  // create input file stream
  ifstream file(fileName);

  if(file.fail()) cerr << "Error opening " << fileName << endl;

  vector<Process> processes;

  // Amalgamate data in specified/expected order
  file >> processQuantity >> switchOverhead_thread >> switchOverhead_process;
  string line, temp; // holder strings
  
	// All the processes
  for(int i = 0; i < processQuantity; i++) {
  	Process process;
  	processType pType;
  	getline(file, line);
  	if(line.empty()) {
  		while(line.empty() | file.eof()) {
  			// ignore empty lines
  			//cout << "1st Empty line!" << endl;
			getline(file, line);
  		}
  	}
  	stringstream ss(line);
  	int process_type;
  	ss >> process.pid >> process.inttype >> process.threadQuantity;
  	// This is the only obvious way to cast to enum
  	process.type = static_cast<processType>(process.inttype); // well and contained inside this process
  	for(int j = 0; j < process.threadQuantity; j++) {
  		getline(file, line);
  		if(line.empty()) {
	  		while(line.empty() | file.eof()) {
	  			// ignore empty lines
	  			// cout << "1st Empty line!" << endl;
				getline(file, line);
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
  			getline(file, line);
  			stringstream ssss(line);
  			ssss >> burst.cpuTime >> burst.ioTime;
  			// could have also used my constructor
  			thread.bursts.push_back(burst);
  		}
  		Burst lastburst;
  		getline(file, line);
  		stringstream lastss(line);
  		lastss >> lastburst.cpuTime;
  		thread.bursts.push_back(lastburst);
  		process.threads.push_back(thread);
  	}
  	processes.push_back(process);
  }
  file.close();
  for(int i = 0; i < processes.size(); i++) {
  	for(int j = 0; j < processes[i].threadQuantity; j++) {
  		Event event;
  		event.time = processes[i].threads[j].arrivalTime;
  		event.type = eventType::THREAD_ARRIVED; // threads have only arrived at this point
  		event.thread = processes[i].threads[j];
  		event.process = processes[i];
  		event.thread_num = j;
  		event.process_num = i;
  		PQ.push(event);
  	}
  }

  // Poop em all back out.
  cout << "------------ALL EVENTS-------------" << endl;
  while(!PQ.empty()) {
  	string eTypeString;
  	string pTypeString;
  	Event event = PQ.top();
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
  	PQ.pop();
  }

  return 0;
}

void argHandler(int argc, char* argv[]) {
  // Will use getopt to ensure proper number of flags are used, if at all
  // Sends errors / help screen if otherwise
  const char* const short_flag = "tva:h";
  // option constructor (name, has_arg, flag, val), if flag ==0, then val is a unique int describing the option.
  // In this case, an int in the form of a char
  const option long_flag[] = {{"per_thread", argNone, 0, 't'},
                              {"verbose", argNone, 0, 'v'},
                              {"algorithm", argNone, 0, 'a'},
                              {"help", argNone, 0, 'h'},
                              {0,0,0,0}};
  fileName = argv[argc-1];
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
      	printf(fileName.c_str());
        cout << endl;
        break;
      case 'v':
        cout << "Flag v" << endl;
      	printf(fileName.c_str());
        cout << endl;
        break;
      case 'a':
        cout << "Flag a" << endl;
      	printf(fileName.c_str());
        cout << endl;
        break;
      case 'h':
        cout << "Flag h" << endl;
      	printf(fileName.c_str());
        cout << endl;
        break;
      default:
      	//strcpy(fileName, optarg);
      	// JUST PRINT THE HELP THING
      	cout << "Default case" << endl;
      	printf(fileName.c_str());
      	break;
    }
  }
}
