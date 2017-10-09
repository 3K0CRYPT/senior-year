#include "process_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>

using namespace std;


ProcessInfo get_process(int pid, const char* basedir) {
	// TODO: implement me
	// TODO: implement cpu_percent
	ProcessInfo currentProcess;

	// Set process id
	currentProcess.pid = pid;

	ifstream f1, f2, f3, f4;
	
	// Convert the char array to a string for the base directory
	string fileName(basedir);
	// Add the process id onto the file location
	string pidDir = "/" + to_string(pid); 
	
	// Add on the statm filename to the file location
	string statm =  "/statm";
	statm = fileName + pidDir + statm;
	
	// Open the statm file and read the appropriate data into the struct
	f1.open(statm);
	string line;
	if (!f1) {
		//cout << "Can't open file" << endl;
		return ProcessInfo();
	}
	while (getline(f1, line)) {
		stringstream ss(line);
		ss >> currentProcess.size >> currentProcess.resident >> currentProcess.share
		>> currentProcess.trs >> currentProcess.lrs >> currentProcess.drs >> currentProcess.dt;
	}
	f1.close();

	// Set the filename to be the stat file
	string stat = "/stat";
	stat = fileName + pidDir + stat;

	// Open the stat file and read the appropriate data into the struct
	f2.open(stat);
	if (!f2) {
		//cout << "Can't open file" << endl;
		return ProcessInfo();
	}
	while (getline(f2, line)) {
		stringstream ss(line);
		string junk;
		ss >> junk >> currentProcess.comm >> currentProcess.state 
		>> currentProcess.ppid >> currentProcess.pgrp >> currentProcess.session >> currentProcess.tty_nr
		>> currentProcess.tpgid >> currentProcess.flags >> currentProcess.minflt >> currentProcess.cminflt
		>> currentProcess.majflt >> currentProcess.cmajflt >> currentProcess.utime >> currentProcess.stime
		>> currentProcess.cutime >> currentProcess.cstime >> currentProcess.priority >> currentProcess.nice
		>> currentProcess.num_threads >> currentProcess.itrealvalue >> currentProcess.starttime 
		>> currentProcess.vsize >> currentProcess.rss >> currentProcess.rsslim >> currentProcess.startcode
		>> currentProcess.endcode >> currentProcess.startstack >> currentProcess.kstkesp >> currentProcess.kstkeip 
		>> currentProcess.signal >> currentProcess.blocked >> currentProcess.sigignore >> currentProcess.sigcatch 
		>> currentProcess.wchan >> currentProcess.nswap >> currentProcess.cnswap >> currentProcess.exit_signal 
		>> currentProcess.processor	>> currentProcess.rt_priority >> currentProcess.policy 
		>> currentProcess.delayacct_blkio_ticks >> currentProcess.guest_time >> currentProcess.cguest_time;
	}
	f2.close();

	// Set the filename to be the status file
	string status = "/status";
	status = fileName + pidDir + status;

	// Open the status file and read the appropriate data into the struct
	f3.open(status);
	if (!f3) {
		//cout << "Can't open file" << endl;
		return ProcessInfo();
	}
	while (getline(f3, line)) {
		stringstream ss(line);
		string junk;
		string value;
		ss >> junk >> value;
		if (junk == "Name:") {
			currentProcess.command_line = value;
		} 
		if (junk == "Tgid:") {
			int temp = stoi(value);
			currentProcess.tgid = temp;
		}
	}

	// Set the filename to be the cmdline file
	string cmdline = "/cmdline";
	cmdline = fileName + pidDir + cmdline;

	f3.close();

	// Open the cmdline file and read the appropriate data into the struct
	f4.open(cmdline);
	if (!f4) {
		//cout << "Can't open file" << endl;
		return ProcessInfo();
	}
	while (getline(f4, line)) {
		// If cmdline is not empty, use the command inside
		if (line != "") {
			// Remove the '\0' characters that are present for some reason
			for (int i = 0; i < line.length() - 1; i++) {
				if (line[i] == '\0') {
					line[i] = ' ';
				}
				line.erase(remove(line.end() - 1, line.end(), '\0'), line.end());
			}
			currentProcess.command_line = line;
		}
	}

	f4.close();
	

	string task = "/task";
	task = fileName + pidDir + task;
	const char *taskDir = task.c_str(); 
	vector<ProcessInfo> threads;

	threads = get_all_processes(taskDir);

	currentProcess.threads = threads;

 	return currentProcess;
}


vector<ProcessInfo> get_all_processes(const char* basedir) {
	// Open base directory of proc
	DIR* directory = opendir(basedir);
	struct dirent *dp;
	string directoryName;
	vector<ProcessInfo> processes;

	// Iterate through all directories/files in location
	if (directory != NULL) {
		while ((dp = readdir(directory)) != NULL) {
			directoryName = dp->d_name;
			bool processDirectory = true;
			
			// Check if directory is a process by checking that its name is all numbers
			for (int i  = 0; i < directoryName.length(); ++i) {
				if (!isdigit(directoryName[i])) {
					processDirectory = false;
				}
			}
			// If a process is found, all get_process function to all the information on the process
			// and add the process object to the vector of all the processes
			if (processDirectory) {
				int pid = stoi(directoryName);
				string temp(basedir);
				processes.push_back(get_process(pid, basedir));
			}
		}
		closedir(directory);
	}
	return processes;
}