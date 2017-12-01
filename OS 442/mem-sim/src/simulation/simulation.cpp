/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include <stdlib.h>
#include "simulation/simulation.h"
#include "iostream"
#include "flag_parser/flag_parser.h"
#include "physical_address/physical_address.h"
#include <map>

using namespace std;

vector<VirtualAddress> virtualAddresses;
map<int, Process*> processIDs;
FlagOptions flags;
int currentEmptyFrame =0;
size_t currentTime=0;
size_t frameToReplace=0;
size_t numPagesInTable = 0;


void Simulation::run() {
for(int i =0; i < virtualAddresses.size(); i++){
	perform_memory_access(virtualAddresses[i]);
	
	currentTime = i+1;
}
}


char Simulation::perform_memory_access(const VirtualAddress& address) {

if(flags.verbose)cout << address << endl;

int workingProcessId = address.process_id;
size_t pageNumber = address.page;
Process* workingProcess = processIDs[workingProcessId];
if(!workingProcess->page_table.rows[pageNumber].present){
	handle_page_fault(workingProcess, pageNumber);
	}
	else{
	if(flags.verbose)cout << "\t->IN MEMORY" << endl;
	}

int vaframe,vaoffset;
vaframe = workingProcess->page_table.rows[pageNumber].frame;
vaoffset = address.offset;
PhysicalAddress physicalAddress = PhysicalAddress(vaframe,vaoffset);
if(flags.verbose)cout << "\t-> physical address " << physicalAddress<<endl;
if(flags.verbose)cout << "\t-> RSS: " << workingProcess->get_rss() << endl;
	
workingProcess->memory_accesses++;
workingProcess->page_table.rows[pageNumber].last_accessed_at = currentTime;
  return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
if(flags.max_frames > process->get_rss()){
	process->page_table.rows[page].frame = currentEmptyFrame;
	process->page_table.rows[page].loaded_at = currentTime;
	currentEmptyFrame++;
	process->page_table.rows[page].present = true;
	}

else if(flags.strategy == ReplacementStrategy::LRU){
size_t lruIndex = process->page_table.get_least_recently_used_page();
process->page_table.rows[lruIndex].present=false;
frameToReplace = process->page_table.rows[lruIndex].frame;
process->page_table.rows[lruIndex].frame = NULL;
}

else {
size_t fifoIndex = process->page_table.get_oldest_page();
process->page_table.rows[fifoIndex].present=false;
frameToReplace = process->page_table.rows[fifoIndex].frame;
process->page_table.rows[fifoIndex].frame = NULL;

}	

process->page_table.rows[page].frame = page;
process->page_table.rows[page].present = true;
process->page_table.rows[page].loaded_at = currentTime;
process->page_faults++;
if(flags.verbose)cout << "\t->PAGE FAULT" << endl;
}
