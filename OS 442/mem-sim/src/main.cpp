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
	int processQuantity;
	string l;
	ifstream in;
	
	in.open(filename);	
	getline(in, l);
	stringstream ss(l);
	ss >> processQuantity;
	
	for (int i = 0; i < processQuantity; i++){
		int pID; string pf;
		getline(in,l);
		while(l.empty()) getline(in,l);
		stringstream ss1(l);
		ss1 >> pID >> pf;
		ifstream in2(pf);
		istreambuf_iterator<char> eos;
		string s(istreambuf_iterator<char>(in2), eos);
		istringstream pStream(s);
		Process* p = Process::read_from_input(pStream);
		processIDs[pID] = p;
		processes.push_back(p);
	}
	while(getline(in,l)){
		if(l.empty()) getline(in,l);
		int pid;
		string virtualAddress_str
		stringstream ss2(l);
		ss2 >> pid >> virtualAddress_str
		VirtualAddress va = VirtualAddress::from_string(pid, virtualAddress_str);
		virtAddresses.push_back(va);
	}
}
	
void processPrint(){
	map<int,Process*>::iterator it;
	for(it = processIDs.begin(); it != processIDs.end(); it++) cout << "Process ID: " << it->first << " size: " << it->second->size() << endl;
	for(int i = 0; i < virtAddresses.size(); i++) cout << virtAddresses[i] << endl;
}



int main(int argc, char** argv) {
	Simulation sim;
	FlagOptions flags;
	parse_flags(argc, argv, flags);
 	fileopen(flags.filename);
	processPrint();
	sim.run();
	return EXIT_SUCCESS;
}