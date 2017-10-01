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
  // TODO: implement me
  double uptime = 0.0;
  ifstream timeFile;
  timeFile.open("./proc/uptime");
  string line;

  if(!timeFile.is_open()){
  	cerr << "Error opening file";
	return 0.0;
  }
  timeFile >> uptime;
  timeFile.close();
  return uptime;
}


SystemInfo get_system_info() {
  // TODO: implement me
  SystemInfo  sysInfo;
  DIR* baseDirectory = opendir(PROC_ROOT);
  struct dirent *dp;
  string filename;
  int count = 0;

  while ((dp = readdir(baseDirectory)) != NULL){
  	filename = dp->d_name;
	bool processDirectory = true;
	for(int i = 0; i < filename.size(); i++){
		if(!isdigit(filename[i])){
			processDirectory = false;
		}
	}
	if(processDirectory){
		count++;
	}
  }

  sysInfo.num_processes = count;
  sysInfo.uptime = get_uptime();


  sysInfo.processes = get_all_processes(PROC_ROOT);


  //find threads n shit
	
  int totThreads = 0;
  int uThreads = 0;
  int kThreads = 0;
  for(int i = 0; i < sysInfo.processes.size(); i++){
 	for (int j = 0; j < sysInfo.processes[i].threads.size(); j++){
		if(sysInfo.processes[i].threads[j].is_thread()){
		totThreads++;
		}
		if(sysInfo.processes[i].threads[j].is_user_thread()){
			uThreads++;
		}
	       if(sysInfo.processes[i].threads[j].is_kernel_thread()){
	       		kThreads++;
	       }	
	}
  }

  sysInfo.num_threads = totThreads;
  sysInfo.num_user_threads = uThreads;
  sysInfo.num_kernel_threads = kThreads;
 
  ifstream statFile;
  statFile.open(PROC_ROOT "/stat");
  string line;

  if(!statFile.is_open()){
  	cerr << "Error opening file";
  }

  while(getline(statFile,line)){
  	stringstream ss(line);
	string attribute, attvalue;
	ss >> attribute >> attvalue;
	if (attribute == "procs_running"){
		sysInfo.num_running = atoi(attvalue.c_str());
	}
  }

  statFile.close();


  sysInfo.load_average = get_load_average();
  sysInfo.memory_info = get_memory_info();
  sysInfo.cpus = get_cpu_info();






  return sysInfo;
}
