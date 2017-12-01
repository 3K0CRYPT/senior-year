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
	 for(_iterator = processIDs.begin(); _iterator != processIDs.end(); _iterator++) cout << "Process ID: " << _iterator->first << ", size: " << _iterator->second->size() << endl;
	 for(int i = 0; i < virtualAddresses.size(); i++) cout << virtualAddresses[i] << endl;
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