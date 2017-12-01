/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation fsstance and fsvoke _iterators
 * run() method.
 */

 #include <cstdlib>
 #include <map>
 #include "simulation/simulation.h"
 #include "flag_parser/flag_parser.h"
 #include "process/process.h"
 #include "virtual_address/virtual_address.h"
 #include <sstream>
 #include <iostream>
 #include <fstream>
 #define no_argument 0
 #define required_argument 1
 #define optional_argument 2
 
 using namespace std;
 
 map<int, Process*> processIDs; vector<Process*> processes; vector<VirtualAddress> virtualAddresses;
 FlagOptions flags;
 
 void readfile(string filename) {
	 int processQuantity; string l; ifstream fs;
	 
	 fs.open(filename);	
	 getline(fs, l);
	 stringstream ss(l);
	 
	 ss >> processQuantity;
	 
	 for (int i =0; i < processQuantity; i++){
		 int pID; string processfile;
		 
		 getline(fs,l);
		 while(l.empty()) getline(fs,l);
		 
		 stringstream ss1(l);
		 ss1 >> pID >> processfile;
		 
		 ifstream fs2(processfile); istreambuf_iterator<char> streamEnd;		
		 string s(istreambuf_iterator<char>(fs2), streamEnd); istringstream streamProcess(s);		
		 
		 Process* p = Process::read_from_input(streamProcess);
		 processIDs[pID] = p;
		 processes.push_back(p);
	 }
	 while(getline(fs,l)){
		 if(l.empty()) getline(fs,l);
			 int pid; string virtualAddress_str; stringstream ss2(l);
			 
			 ss2 >> pid >> virtualAddress_str;
			 
			 VirtualAddress va = VirtualAddress::from_string(pid, virtualAddress_str);
			 virtualAddresses.push_back(va);
	 }
 }
	 
 void processPrint(){
	map<int,Process*>::iterator _iterator;
	int memAccesses=0;
	int pageFaults=0;
	int usedFrames=0;
	for(_iterator = processIDs.begin(); _iterator != processIDs.end(); _iterator++){
		//cout << "ProcessId " << _iterator->first << " size: " << _iterator->second->size() << endl;
		cout << "Process " << _iterator->first << "\tMemory Accesses: " << _iterator->second->memory_accesses <<
			"\tPage Faults: " << _iterator->second->page_faults << "\tFree Frames " << (flags.max_frames - _iterator->second->get_rss()) <<
			"\tFault Rate: " << _iterator->second->get_fault_percent() <<
			"\tRSS: " << _iterator->second->get_rss() << endl;
		memAccesses += _iterator->second->memory_accesses;
		pageFaults += _iterator->second->page_faults;
		usedFrames += (_iterator->second->get_rss());
	}
	cout << "TOTAL MEMORY ACCESSES: " << memAccesses <<endl;
	cout << "TOTAL PAGE FAULTS: " << pageFaults <<endl;
	cout << "TOTAL FREE FRAMES: " << 512 - usedFrames << endl;
 }
 
 
 int main(int argc, char** argv) {
	 Simulation _simulation;
	 FlagOptions flags;
	 parse_flags(argc, argv, flags);
	  readfile(flags.filename);
	 processPrint();
	 _simulation.run();
	 return EXIT_SUCCESS;
 }