#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


MemoryInfo get_memory_info() {
	MemoryInfo memInfo;

	ifstream f;
	f.open("./proc/meminfo");
	string line;
	string title, value;


	if (!f) {
		cout << "Can't open file" << endl;
		return MemoryInfo();
	}
	while (getline(f, line)) {
		stringstream ss(line);
		ss >> title >> value;
		int temp;
		if (title == "MemTotal:") {
			temp = stoi(value);
			memInfo.total_memory = temp;
		}
		if (title == "MemFree:") {
			temp = stoi(value);
			memInfo.free_memory = temp;
		}
		if (title == "Buffers:") {
			temp = stoi(value);
			memInfo.buffers_memory = temp;
		}
		if (title == "Cached:") {
			temp = stoi(value);
			memInfo.cached_memory = temp;
		}
		if (title == "SwapTotal:") {
			temp = stoi(value);
			memInfo.total_swap = temp;
		}
		if (title == "SwapFree:") {
			temp = stoi(value);
			memInfo.free_swap = temp;
		}
	
	}
	f.close();

  return memInfo;
}
