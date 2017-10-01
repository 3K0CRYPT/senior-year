#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


MemoryInfo get_memory_info() {
  // TODO: implement me

  MemoryInfo mem_info;

  ifstream memInfo(PROC_ROOT "/meminfo");

  if(!memInfo) {
  	cerr << "Unable to read from /proc/meminfo" << endl;
  	return mem_info;
  }

  string line;
  string prefix;

  while(getline(memInfo, line)) {
  	istringstream lineStream(line);
  	lineStream >> prefix;

  	if(prefix == ("MemTotal:")) {
  		lineStream >> mem_info.total_memory;
  	}
  	else if(prefix == ("MemFree:")) {
  		lineStream >> mem_info.free_memory;
  	}
  	else if(prefix == ("Buffers:")) {
  		lineStream >> mem_info.buffers_memory;
  	}
  	else if(prefix == ("Cached:")) {
  		lineStream >> mem_info.cached_memory;
  	}
  	else if(prefix == ("SwapTotal:")) {
  		lineStream >> mem_info.total_swap;
  	}
  	else if(prefix == ("SwapFree:")) {
  		lineStream >> mem_info.free_swap;
  	}

  }

  return mem_info;
}
