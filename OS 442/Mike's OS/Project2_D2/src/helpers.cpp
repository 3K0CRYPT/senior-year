#include "info/helpers.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <getopt.h>

using namespace std;

vector<Process> readFile(string fileName) {
	vector<Process> processes;

	ifstream f;
	f.open(fileName);
	string line;
	if (!f) {
		cout << "Can't open file" << endl;
	}
	else {
		getline(f,line);
		stringstream ss1(line);
		ss1 >> num_processes >> thread_switch_overhead >> process_switch_overhead;

		for (int i = 0; i < num_processes; i++) {
			Process currentProcess;

			getline(f,line);
			while (line.empty()) {
				getline(f,line);
			}
			stringstream ss2(line);
			int temp;
			ss2 >> currentProcess.pid >> temp >> currentProcess.num_threads;
			num_threads += currentProcess.num_threads; 

			currentProcess.type = static_cast<Process::Process_Type>(temp);
			
			for (int j = 0; j < currentProcess.num_threads; j++) {
				Thread currentThread;
				currentThread.parent_process_id = currentProcess.pid;
				getline(f,line);
				while (line.empty()) {
					getline(f,line);
				}
				stringstream ss3(line);
				ss3 >> currentThread.arrival_time >> currentThread.num_CPU_bursts;
				currentThread.state = Thread::Thread_State::NEW;
				currentThread.thread_number = j;
				
				for (int k = 0; k < currentThread.num_CPU_bursts - 1; k++) {
					Burst currentBurst;
					getline(f,line);
					while (line.empty()) {
						getline(f,line);
					}
					stringstream ss4(line);
					int cpu_time, io_time;

					ss4 >> cpu_time >> io_time;
					currentBurst.type = Burst::Burst_Type::CPU;
					currentBurst.total_time = cpu_time;
					currentBurst.remaining_time = cpu_time;
					//currentThread.bursts.push_back(currentBurst);
					currentThread.bursts.push(currentBurst);

					currentBurst.type = Burst::Burst_Type::IO;
					currentBurst.total_time = io_time;
					currentBurst.remaining_time = io_time;
					//currentThread.bursts.push_back(currentBurst);
					currentThread.bursts.push(currentBurst);
				}
				
				Burst lastBurst;
				getline(f,line);
				while (line.empty()) {
					getline(f,line);
				}
				stringstream ss5(line);
				ss5 >> lastBurst.total_time;
				lastBurst.type = Burst::Burst_Type::CPU;
				lastBurst.remaining_time = lastBurst.total_time;

				//currentThread.bursts.push_back(lastBurst);
				currentThread.bursts.push(lastBurst);
				currentProcess.threads.push_back(currentThread);
			}
		processes.push_back(currentProcess);
		}
		
	}
	f.close();
	return processes;
}

// Prints the help message and exits
void printHelp() {
  printf("\r----------------------Simulator Help--------------------\n");
  printf("\rAvailable Flags:\n");
  printf("\r-t OR --per_thread Output additional per-thread statistics for arrival time, service time, etc\n");
  printf("\r-v OR --verbose Output information about every state-changing event and scheduling decision\n");
  printf("\r-a OR --algorithm ALGORITH Allows user to choose the scheduling algorithm used. FCFS is default");
  printf("\r-h OR --help Displays this help message\n");
  // endwin();
  exit(EXIT_SUCCESS);
}

// Method to handle the flags
void processArguments(int argc, char** argv) {
  const char* const short_options = "t::v::a:h";
  const option long_options[] = {
    {"per_thread", no_argument, 0, 't'},
    {"verbose", no_argument, 0, 'v'},
    {"algorithm", required_argument, 0, 'a'},
    {"help", no_argument, 0, 'h'}
  };  
  int option_index = 0;
  int opt;

  while (true) {
    opt = getopt_long(argc, argv, short_options, long_options, &option_index);
    if (opt == -1)
      break;

  	
    switch(opt) {
     // If -t or --per_thread flag is used, 
      case 't':
	    {
	    	printf("Thread flag selected\n");
	    	per_thread_mode = true;
	    }
      break;

      // If -v or --verbose flag is used,
      case 'v':
        {
        	printf("Verbose flag selected\n");
        	verbose_mode = true;
        }
      break;

      // If -a or --algorithm flag is used,
      case 'a':
		{
			printf("Algorithm flag selected\n");
			string choice = argv[optind-1];
			//RR, PRIORITY, CUSTOM

			if (choice == "FCFS") {
				selected_algorithm = FCFS;
			}

			else if (choice == "RR") {
				selected_algorithm = RR;
			}

			else if (choice == "PRIORITY") {
				selected_algorithm = PRIORITY;
			}

			else if (choice == "CUSTOM") {
				selected_algorithm = CUSTOM;
			}
			
			else {
				printf("Selected algorithm is invalid. Defaulting to FCFS.\n");
				printf("YO");
			}
			
		}
      break;

      // If -h or --help flag is used or any invalid flags are used, print the help message and exit
      case 'h':
      default:
        {
        	printHelp();
       		break;
       	}

    }
  }
}