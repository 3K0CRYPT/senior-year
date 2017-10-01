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


	// read in from proc/[pid]/stat, proc/[pid]/statm, proc/[pid]/stat,
	// proc/[pid]/status, proc/[pid]/cmdline, and proc/[pid]/task
	// to get all process variables. There are a TON of them
	ProcessInfo PI;
	string line, temp, temp2;

	// Set PID
	PI.pid = pid;

	// Get PID directory as string
	string base_path(basedir);
	ostringstream pid_stringstream;
	pid_stringstream << pid;
	string pid_path = "/" + pid_stringstream.str();
	string proc_path_statm = base_path + pid_path + "/statm";

	// Open the file
	ifstream proc_file_statm;
	proc_file_statm.open(proc_path_statm.c_str());
	if(!proc_file_statm) {
		cout << "Cannot open proc/[pid]/statm";
		return ProcessInfo();
	}
	else {
		while(getline(proc_file_statm, line)) {
			stringstream proc_stream(line);
			proc_stream
				>> PI.size
				>> PI.resident
				>> PI.share
				>> PI.trs
				>> PI.lrs
				>> PI.drs
				>> PI.dt;
		}
		proc_file_statm.close();
	}

	// Repeat for /stat
	string proc_path_stat = base_path + pid_path + "/stat";
	ifstream proc_file_stat;
	proc_file_stat.open(proc_path_stat.c_str());
	if(!proc_file_stat) {
		cout << "Cannot open proc/[pid]/stat";
		return ProcessInfo();
	}
	else {
		while(getline(proc_file_stat, line)) {
			stringstream proc_stream(line);
			proc_stream
				>> temp
				>> PI.comm
				>> PI.state
				>> PI.ppid
				>> PI.pgrp
				>> PI.session
				>> PI.tty_nr
				>> PI.tpgid
				>> PI.flags
				>> PI.minflt
				>> PI.cminflt
				>> PI.majflt
				>> PI.cmajflt
				>> PI.utime
				>> PI.stime
				>> PI.cutime
				>> PI.cstime
				>> PI.priority
				>> PI.nice
				>> PI.num_threads
				>> PI.itrealvalue
				>> PI.starttime
				>> PI.vsize
				>> PI.rss
				>> PI.rsslim
				>> PI.startcode
				>> PI.endcode
				>> PI.startstack
				>> PI.kstkesp
				>> PI.kstkeip
				>> PI.signal
				>> PI.blocked
				>> PI.sigignore
				>> PI.sigcatch
				>> PI.wchan
				>> PI.nswap
				>> PI.cnswap
				>> PI.exit_signal
				>> PI.processor
				>> PI.rt_priority
				>> PI.policy
				>> PI.delayacct_blkio_ticks
				>> PI.guest_time
				>> PI.cguest_time;
		}
		proc_file_stat.close();
	}

	// Repeat for /status
	string proc_path_status = base_path + pid_path + "/status";
	ifstream proc_file_status;
	proc_file_status.open(proc_path_status.c_str());
	if(!proc_file_status) {
		cout << "Cannot open proc/[pid]/status";
		return ProcessInfo();
	}
	else {
		while(getline(proc_file_status, line)) {
			stringstream proc_stream(line);
			proc_stream
				>> temp
				>> temp2;
			if (temp == "Name:") {
				PI.command_line = temp2;
			}
			if (temp == "Tgid:") {
				istringstream is(temp2);
				int tgid;
				if(is >> tgid) {
					PI.tgid = tgid;
				}
			}
		}
		proc_file_status.close();
	}

	// Repeat for /cmdline
	string proc_path_cmd = base_path + pid_path + "/cmdline";
	ifstream proc_file_cmd;
	proc_file_cmd.open(proc_path_cmd.c_str());
	if(!proc_file_cmd) {
		cout << "Cannot open proc/[pid]/cmdline";
		return ProcessInfo();
	}
	else {
		while(getline(proc_file_cmd, line)) {
			// Check for command
			if (line != "") {
				// remove null characters
				for (int i = 0; i < line.length() - 1; i++) {
					if(line[i] == '\0') {
						line[i] = ' ';
					}
					line.erase(remove(line.end() - 1, line.end(), '\0'), line.end());
				}
				PI.command_line = line;
			}
		}
		proc_file_cmd.close();
	}

	// Repeat for /task
	string proc_path_task = base_path + pid_path + "/task";
	const char* dir_task = proc_path_task.c_str();

	PI.threads = get_all_processes(dir_task);

	return PI;
}


vector<ProcessInfo> get_all_processes(const char* basedir) {

	// Hard part is over, now just call get process for each process
	vector<ProcessInfo> PIs;
	string dName;

	DIR* dir = opendir(basedir);

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
        		// dName should be all numbers
			istringstream ispid(dName);
			int pid;
			if(ispid >> pid) {
				PIs.push_back(get_process(pid, basedir));
        		}
        	}
        }

        entry = readdir(dir);
    }

    closedir(dir);
	}
	else {
		//cout << "Directory was NULL" << endl;
	}

  
  return PIs;
}
