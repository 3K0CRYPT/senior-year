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
	ProcessInfo givenProcess;

	givenProcess.pid = pid;
	ifstream file1, file2, file3, file4;
	string fName(basedir);
	stringstream ss;
	ss << pid;
	string pidString = ss.str();
	string pidDirectory = "/" + pidString;
	string line;


	string statmFile = "./" + fName + pidDirectory + "/statm";
	file1.open(statmFile.c_str());
	if(!file1.is_open()) { 
		cerr << "Error opening file";
		return ProcessInfo();
	}



	string statFile = fName + pidDirectory + "/stat";
	file2.open(statFile.c_str());
	if(!file2.is_open()){
		cerr << "Error opening file";
		return ProcessInfo();
	}


	string statusFile = fName + pidDirectory + "/status";
	file3.open(statusFile.c_str());
	if(!file3.is_open()){
		cerr << "Error opening file";
		return ProcessInfo();
	}

	string cmdlineFile = fName + pidDirectory + "/cmdline";
	file4.open(cmdlineFile.c_str());
	if(!file4.is_open()){
		cerr << "Error opening file";
		return ProcessInfo();
	}

	
	while(getline(file1, line)){
	stringstream ss1(line);
	ss1 >> givenProcess.size >> givenProcess.resident >> givenProcess.share >> givenProcess.trs >> givenProcess.lrs >> givenProcess.drs >> givenProcess.dt;
	}

	 while (getline(file2, line)) {
		 stringstream ss2(line);
		 string crap;
		 ss2 >> crap >> givenProcess.comm >> givenProcess.state  >> givenProcess.ppid >> givenProcess.pgrp >> givenProcess.session
		 >> givenProcess.tty_nr >> givenProcess.tpgid >> givenProcess.flags >> givenProcess.minflt >> givenProcess.cminflt
		 >> givenProcess.majflt >> givenProcess.cmajflt >> givenProcess.utime >> givenProcess.stime >> givenProcess.cutime
		 >> givenProcess.cstime >> givenProcess.priority >> givenProcess.nice >> givenProcess.num_threads >> givenProcess.itrealvalue
		 >> givenProcess.starttime >> givenProcess.vsize >> givenProcess.rss >> givenProcess.rsslim >> givenProcess.startcode
		 >> givenProcess.endcode >> givenProcess.startstack >> givenProcess.kstkesp >> givenProcess.kstkeip >> givenProcess.signal 
		 >> givenProcess.blocked >> givenProcess.sigignore >> givenProcess.sigcatch >> givenProcess.wchan >> givenProcess.nswap 
		 >> givenProcess.cnswap >> givenProcess.exit_signal >> givenProcess.processor >> givenProcess.rt_priority
		 >> givenProcess.policy >> givenProcess.delayacct_blkio_ticks >> givenProcess.guest_time >> givenProcess.cguest_time;
		 //seriously why is this a thing.
	 }

	 while(getline(file3,line)){
		stringstream ss3(line);
		string crap, value;
		ss3 >> crap >> value;
		if(crap == "Name:"){
		       givenProcess.command_line = value;
		}
 		if(crap == "Tgid:"){
			stringstream tempss;
			tempss << value;
			int tempVal = atoi(value.c_str()); // tempss.ss();
			givenProcess.tgid = tempVal;
		}		
	 }

	 while(getline(file4,line)){
			 if (line != ""){
			 for(int i = 0; i < line.length(); i++){
			 	if (line[i] == '\0'){
					line[i] = ' ';
			 }
			 line.erase(remove(line.end() -1,line.end(), '\0'), line.end());
			 }
			 givenProcess.command_line = line;

			 }

			 }

	 file1.close();
	 file2.close();
	 file3.close();
	 file4.close();

	 string taskString = fName + pidDirectory + "/task";
	 const char *taskdir = taskString.c_str();
	 //vector <ProcessInfo> threads = get_all_processes(taskdir);
	 
	 givenProcess.threads = get_all_processes(taskdir);
  return givenProcess;
}


vector<ProcessInfo> get_all_processes(const char* basedir) {
  // TODO: implement me
  DIR* directory = opendir(basedir);
  struct dirent *dp;
  string directName;
  vector <ProcessInfo> processes;
	
  if(directory != NULL){
  while((dp = readdir(directory)) != NULL){
  	directName = dp->d_name;
	bool processDirectory = true;

	for(int i = 0; i < directName.length(); i++){
		if(!isdigit(directName[i])){
			processDirectory = false;
		}
	}

	if(processDirectory){
		stringstream tempss;
		tempss << directName;
		int pid = atoi(directName.c_str());
		string temp(basedir);
		processes.push_back(get_process(pid,basedir));
	}

  }
  closedir(directory);
  }
  

  return processes;
}
