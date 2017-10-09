#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


vector<CpuInfo> get_cpu_info() {
  // TODO: implement me
	vector<CpuInfo> infos;
	ifstream f;
	f.open("./proc/stat");
	string line;
	if (!f) {
		cout << "Can't open file" << endl;
		return vector<CpuInfo>();
	}
	
	while (getline(f, line)) {
			string temp;
			CpuInfo current;
			stringstream ss(line);
			ss >> temp >> current.user_time >> current.nice_time >> current.system_time
			>> current.idle_time >> current.io_wait_time >> current.irq_time
			>> current.softirq_time >> current.steal_time >> current.guest_time 
			>> current.guest_nice_time;
		if (temp.substr(0, 3) == "cpu") {
			infos.push_back(current);
		}
		else {
			break;
		}
	}
	f.close();
 	
 	return infos;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
  CpuInfo difference;
  difference.user_time = lhs.user_time - rhs.user_time;
  difference.nice_time = lhs.nice_time - rhs.nice_time;
  difference.system_time = lhs.system_time - rhs.system_time;
  difference.idle_time = lhs.idle_time - rhs.idle_time;
  difference.io_wait_time = lhs.io_wait_time - rhs.io_wait_time;
  difference.irq_time = lhs.irq_time - rhs.irq_time;
  difference.softirq_time = lhs.softirq_time - rhs.softirq_time;
  difference.steal_time = lhs.steal_time - rhs.steal_time;
  difference.guest_time = lhs.guest_time - rhs.guest_time;
  difference.guest_nice_time = lhs.guest_nice_time - rhs.guest_nice_time;
  return difference;
}
