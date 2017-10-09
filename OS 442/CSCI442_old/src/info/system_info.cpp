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
	double uptime = 0.0;
	ifstream f;
	f.open("./proc/uptime");
	string line;

	if (!f) {
		cerr << "Can't open file" << endl;
		return 1;
	}
	
	f >> uptime;
	f.close();

	return uptime;
}


SystemInfo get_system_info() {
  // TODO: implement me
  SystemInfo sysInfo;
  ProcessInfo processInfo;

  DIR* directory = opendir("./proc");
	struct dirent *dp;
	string fileName;
	int count = 0;

	while ((dp = readdir(directory)) != NULL) {
		fileName = dp->d_name;
		bool processDirectory = true;
		for (int i  = 0; i < fileName.length(); ++i) {
			if (!isdigit(fileName[i])) {
				processDirectory = false;
			}
		}
		if (processDirectory) {
			count++;
		}
		
	}
	sysInfo.num_processes = count;
	sysInfo.uptime = get_uptime();

	sysInfo.processes = get_all_processes(PROC_ROOT);

	// Get number of threads
	int thread_count = 0;
	int user_thread_count = 0;
	int kernel_thread_count = 0;
	for (int i = 0; i < sysInfo.processes.size(); i++) {
		//cout << sysInfo.processes[i].pid << "Num threads: " << sysInfo.processes[i].threads.size() << endl;
		for (int j = 0; j < sysInfo.processes[i].threads.size(); j++) {
			
			if (sysInfo.processes[i].threads[j].is_thread()) {
				++thread_count;
			}
			else {
				cout << "NOT A THREAD" << endl;
			}
			if (sysInfo.processes[i].threads[j].is_user_thread()) {
				++user_thread_count;
			}
			if (sysInfo.processes[i].threads[j].is_kernel_thread()) {
				++kernel_thread_count;
			}
		}
	}
	sysInfo.num_threads = thread_count;
	sysInfo.num_user_threads = user_thread_count;
	sysInfo.num_kernel_threads = kernel_thread_count;

	// Get the number of running processes from stat file
	ifstream f;
	f.open("./proc/stat");
	string line;
	if (!f) {
		cout << "Can't open file" << endl;
	}
	while(getline(f, line)) {
		stringstream ss(line);
		string title, value;
		ss >> title >> value;
		if (title == "procs_running") {
			sysInfo.num_running = stoi(value);
		}
	}
	f.close();
	
	sysInfo.load_average = get_load_average();
	sysInfo.memory_info = get_memory_info();
	sysInfo.cpus = get_cpu_info();


	closedir(directory);
	return sysInfo;
}
