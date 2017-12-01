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

map<int, Process*> procIds;
vector<Process*> processes;
vector<VirtualAddress> virtAddresses;
FlagOptions flags;


void readFile(string filename){
ifstream in;
in.open(filename);
int numProcesses;
string line;
getline(in, line);
stringstream ss(line);
ss >> numProcesses;
for (int i =0; i < numProcesses; i++){
	int processId;
	string processfile;
	getline(in,line);
	while(line.empty()){getline(in,line);}
	stringstream ss1(line);
	ss1 >> processId >> processfile;
	ifstream inFile(processfile);
	istreambuf_iterator<char> eos;
  	string s(istreambuf_iterator<char>(inFile), eos);
	istringstream process_stream(s);
	Process* p = Process::read_from_input(process_stream);
	procIds[processId] = p;
	processes.push_back(p);
}
while(getline(in,line)){
	if(line.empty()) getline(in,line);
		int pid;
		string virtAdd;
		stringstream ss2(line);
		ss2 >> pid >> virtAdd;
		VirtualAddress va = VirtualAddress::from_string(pid, virtAdd);
		virtAddresses.push_back(va);
}

}

void printProcesses(){
map<int,Process*>::iterator it;
int memAccesses=0;
int pageFaults=0;
int usedFrames=0;
for(it = procIds.begin(); it != procIds.end(); it++){
	
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
for(int i = 0; i < virtAddresses.size(); i++){
	
}
}

int main(int argc, char** argv) {
	Simulation sim;

	parse_flags(argc, argv, flags);
	readFile (flags.filename);
	sim.run();
	printProcesses();


  return EXIT_SUCCESS;
}
