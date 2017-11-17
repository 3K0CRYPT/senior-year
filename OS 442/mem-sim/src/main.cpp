/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
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



void fileopen(string filename){
	int numProcesses;
	string line;
	ifstream in;
	in.open(filename);	
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
	for(it = procIds.begin(); it != procIds.end(); it++){
		cout << "ProcessId " << it->first << " size: " << it->second->size() << endl;
	}
	for(int i = 0; i < virtAddresses.size(); i++) cout << virtAddresses[i] << endl;
	}



int main(int argc, char** argv) {
	Simulation sim;
	FlagOptions flags;
	parse_flags(argc, argv, flags);
 	fileopen(flags.filename);
	printProcesses();
	sim.run();
	return EXIT_SUCCESS;
}