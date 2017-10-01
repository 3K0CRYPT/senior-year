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

void read_file(string filename);
FlagOptions flags;

// Simulation variables
vector<VirtualAddress> addresses;
map<int, Process*> processes; // look up table

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  // TODO: implement me
  parse_flags(argc, argv, flags);
  read_file(flags.filename);
  Simulation sim;
  sim.flags = flags;
  sim.addresses = addresses;
  sim.processes = processes;
  sim.run();
  sim.print_results();
  
  return EXIT_SUCCESS;
}

void read_file(string filename) {
	ifstream in(filename);

	int num_procs;
	string line;
	getline(in, line);
	stringstream sstream(line);
	sstream >> num_procs;

	// Process file stuff
	for(int i = 0; i < num_procs; i++) {
		getline(in, line);
		while(line.empty()) {
			getline(in, line);
		}
		stringstream ssstream(line);
		int pid;
		string process_file;
		ssstream >> pid >> process_file;
		ifstream proc_file_stream(process_file);
		// Only, only, only way to correctly read in the processes
		istreambuf_iterator<char> eos;
		string s(istreambuf_iterator<char> proc_file_stream, eos);
		istringstream proc_stream(s);
		Process* proc = Process::read_from_input(proc_stream);
		processes[pid] = proc;
	}

	// Virtual addresses
	while(getline(in, line)) {
		while(line.empty()) {
			getline(in, line);
		}
		int pid;
		string virtual_address;
		stringstream sssstream(line);
		sssstream >> pid >> virtual_address;
		addresses.push_back(VirtualAddress::from_string(pid, virtual_address));
	}
}
