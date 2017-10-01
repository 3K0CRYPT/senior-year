#include "system_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "process_info.h"
#include "load_average_info.h"
#include "memory_info.h"

using namespace std;


double get_uptime() {
  double timerino;
  ifstream upFile(PROC_ROOT "/uptime");

  if (!upFile) {
  	cerr << "Unable to read from /proc/uptime" << endl;
  	return 0.0;
  }

  upFile >> timerino;

  return timerino;

}

unsigned long long get_procs_running() {
	unsigned long long procsRunning;

	ifstream prFile(PROC_ROOT "/stat"); 

	if (!prFile) {
		cerr << "Unable to read from /proc/stat" << endl;
		return 0;
	}

	string line;
  string prefix;

  while(getline(prFile, line)) {
  	istringstream lineStream(line);
  	lineStream >> prefix;

  	if(prefix == ("procs_running")) {
  		lineStream >> procsRunning;
  	}
  }

  return procsRunning;
}

unsigned long long get_num_procs() {
	unsigned long long procsTotal = 0;

	const char* PATH = "./proc";

    DIR* dir = opendir(PATH);

    if(dir != NULL) {
    struct dirent *entry = readdir(dir);
    while (entry != NULL)
    {
    	string dName = entry->d_name;
        if (entry->d_type == DT_DIR) {
        	bool isProcess = true;
        	for (int i = 0; i < dName.length(); ++i) {
        		if(!isdigit(dName[i])) {
        			isProcess = false;
        		}
        	}
        	if(isProcess) {
        		procsTotal++;
        	}
        }

        entry = readdir(dir);
    }

    closedir(dir);
	}
	else {
		//cout << "Directory was NULL" << endl;
	}
  return procsTotal;
}

vector<unsigned long long> get_threads_info() {
	vector<unsigned long long> TI;
	vector<ProcessInfo> processes = get_all_processes(PROC_ROOT);

	//cout << "Number of processes is " << processes.size() << endl;

	unsigned long long threads_total = 0;
	unsigned long long threads_user = 0;
	unsigned long long threads_kernel = 0;

	for(int i = 0; i < processes.size(); i++) {
		//cout << "Number of threads in process " << i << " is " << processes[i].threads.size() << endl;
		for(int j = 0; j < processes[i].threads.size(); j++) {
			if(processes[i].threads[j].is_thread()) {
				threads_total++;
			}
			if(processes[i].threads[j].is_user_thread()) {
				threads_user++;
			}
			if(processes[i].threads[j].is_kernel_thread()) {
				threads_kernel++;
			}
		}
	}
	return TI;
}



SystemInfo get_system_info() {
  SystemInfo SI;
  SI.uptime = get_uptime();
  SI.num_running = get_procs_running();
  SI.num_processes = get_num_procs();
  SI.processes = get_all_processes(PROC_ROOT);
  vector<unsigned long long> threadInfo = get_threads_info();
  if(threadInfo.size() == 3) {
  	SI.num_threads = threadInfo[0];
  	SI.num_user_threads = threadInfo[1];
  	SI.num_kernel_threads = threadInfo[2];
  }

  SI.load_average = get_load_average();
  SI.memory_info = get_memory_info();
  SI.cpus = get_cpu_info();

  return SI;
}
