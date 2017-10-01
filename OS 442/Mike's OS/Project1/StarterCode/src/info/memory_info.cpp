#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


MemoryInfo get_memory_info() {
  // TODO: implement me
  MemoryInfo memoryInformation;
  ifstream memFile;
  memFile.open(PROC_ROOT "/meminfo");
  string line;
  string attribute, attvalue;

  while(getline(memFile,line)){
	stringstream ss(line);
	ss >> attribute >> attvalue;
	int temp;
	if(attribute == "MemTotal:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.total_memory = temp;
	}
	if(attribute == "MemFree:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.free_memory = temp;
	}
	if(attribute == "Buffers:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.buffers_memory = temp;
	}
	if(attribute == "Cached:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.cached_memory = temp;
	}
	if(attribute == "SwapTotal:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.total_swap = temp;
	}
	if(attribute == "SwapFree:"){
		temp = atoi(attvalue.c_str());
		memoryInformation.free_swap = temp;
	}
	

  }

  memFile.close();
  return memoryInformation;
}
