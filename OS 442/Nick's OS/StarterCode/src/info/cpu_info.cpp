#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


vector<CpuInfo> get_cpu_info() {
  vector<CpuInfo> info;

  ifstream cpuInfo(PROC_ROOT "/stat");

  if (!cpuInfo) {
  	cerr << "Unable to read from /proc/stat" << endl;
  }

  string line, prefix;

  CpuInfo* ptr = new CpuInfo;
  while( getline(cpuInfo, line)) {
  	istringstream lineStream(line);

  	lineStream >> prefix;

  	if(prefix.substr(0, 3) == "cpu") {
  		lineStream >> ptr->user_time;
  		lineStream >> ptr->nice_time;
  		lineStream >> ptr->system_time;
  		lineStream >> ptr->idle_time;
  		lineStream >> ptr->io_wait_time;
  		lineStream >> ptr->irq_time;
  		lineStream >> ptr->softirq_time;
  		lineStream >> ptr->steal_time;
  		lineStream >> ptr->guest_time;
  		lineStream >> ptr->guest_nice_time;
  	}
  	else{break;}

  	info.push_back(*ptr);
  	delete ptr;
  	ptr = new CpuInfo;

  }

  delete ptr;

  cpuInfo.close();

  return info;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
  CpuInfo subtraction;

  subtraction.user_time = lhs.user_time - rhs.user_time;
  subtraction.nice_time = lhs.nice_time - rhs.nice_time;
  subtraction.system_time = lhs.system_time - rhs.system_time;
  subtraction.idle_time = lhs.idle_time - rhs.idle_time;
  subtraction.io_wait_time = lhs.io_wait_time - rhs.io_wait_time;
  subtraction.irq_time = lhs.irq_time - rhs.irq_time;
  subtraction.softirq_time = lhs.softirq_time - rhs.softirq_time;
  subtraction.steal_time = lhs.steal_time - rhs.steal_time;
  subtraction.guest_time = lhs.guest_time - rhs.guest_time;
  subtraction.guest_nice_time = lhs.guest_nice_time - rhs.guest_nice_time;

  return subtraction;
}
