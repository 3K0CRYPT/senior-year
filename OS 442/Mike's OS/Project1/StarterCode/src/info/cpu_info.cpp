#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


vector<CpuInfo> get_cpu_info() {
  // TODO: implement me
  vector<CpuInfo> civ;
  ifstream fp("./proc/stat");
  if (!fp.is_open()){
	  cout << "LOL" << endl;
	  return vector<CpuInfo>();
  }
  string line;
  CpuInfo cis;
  while(getline(fp,line)){
	stringstream ss(line);
  string name;
	ss >> name >> cis.user_time >> cis.nice_time >> cis.system_time >> cis.idle_time >> cis.io_wait_time >> cis.irq_time >> cis.softirq_time >> cis.steal_time >> cis.guest_time >> cis.guest_nice_time;
	if (name.substr(0,3)=="cpu") {
		civ.push_back(cis);
	}
	else break;
  }
  fp.close();
  return civ;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
  // TODO: implement me
  return CpuInfo();
}
