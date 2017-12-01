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

map<int, Process*> processIDs; vector<Process*> processes; vector<VirtualAddress> virtualAddresses; FlagOptions flags;


void fileRead(string filename){
	ifstream in; in.open(filename); int processQuantity; string line; getline(in, line); stringstream ss(line);
	ss >> processQuantity;
	for (int i =0; i < processQuantity; i++) {
		int processId;
		string _line;
		getline(in,line);
		while(line.empty()){getline(in,line);}
		stringstream ss1(line);
		ss1 >> processId >> _line;
		ifstream inFile(_line);
		istreambuf_iterator<char> eos;
		string s(istreambuf_iterator<char>(inFile), eos);
		istringstream process_stream(s);
		Process* p = Process::read_from_input(process_stream);
		processIDs[processId] = p;
		processes.push_back(p);
	}
	while(getline(in,line)){
		if(line.empty()) getline(in,line);
		int pid;
		string virtualAddress;
		stringstream ss2(line);
		ss2 >> pid >> virtualAddress;
		VirtualAddress va = VirtualAddress::from_string(pid, virtualAddress);
		virtualAddresses.push_back(va);
		}
}

void processPrint(){
	map<int,Process*>::iterator it;
	int memAccesses=0, pageFaults=0, usedFrames=0;
	for(it = processIDs.begin(); it != processIDs.end(); it++){
		cout << "Process " << it->first << "\tMemory Accesses: " << it->second->memory_accesses <<
			"\tPage Faults: " << it->second->page_faults << "\tFree Frames " << (flags.max_frames - it->second->get_rss()) <<
			"\tFault Rate: " << it->second->get_fault_percent() <<
			"\tRSS: " << it->second->get_rss() << endl;
		memAccesses += it->second->memory_accesses;
		pageFaults += it->second->page_faults;
		usedFrames += (it->second->get_rss());
	}
	cout << "TOTAL MEMORY ACCESSES: " << memAccesses <<endl;
	cout << "TOTAL PAGE FAULTS: " << pageFaults <<endl;
	cout << "TOTAL FREE FRAMES: " << 512 - usedFrames << endl;
}

int main(int argc, char** argv) {
	Simulation sim;

	parse_flags(argc, argv, flags);
	fileRead(flags.filename);
	sim.run();
	processPrint();

  return EXIT_SUCCESS;
}
