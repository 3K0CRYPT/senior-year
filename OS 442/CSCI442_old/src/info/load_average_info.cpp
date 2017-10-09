#include "load_average_info.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


LoadAverageInfo get_load_average() {
	LoadAverageInfo laInfo;
	ifstream f;
	f.open("./proc/loadavg");
	string line;
	if (!f) {
		cout << "Can't open file" << endl;
		return LoadAverageInfo();
	}
	while (getline(f, line)) {
		stringstream ss(line);
		ss >> laInfo.one_min >> laInfo.five_mins >> laInfo.fifteen_mins;
	}
	f.close();
  return laInfo;
}
