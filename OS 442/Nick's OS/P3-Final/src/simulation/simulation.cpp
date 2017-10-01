/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#pragma once

#include <stdlib.h>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"
#include <iostream>
#include <sstream>
#include <fstream>

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;

int empty_frame_index = 0;
size_t current_time = 0;
size_t least_recently_used_index = 0;
size_t oldest_page_index = 0;
size_t victim_frame_index = 0;
size_t num_pages = 0;

// FROM simulation.h
  // FlagOptions flags;
  // std::vector<VirtualAddress> addresses;
  // std::map<int, Process*> processes; // look up table


void Simulation::run() {

  // access each virtual address
  for(int i = 0; i < addresses.size(); i++) {
  	 perform_memory_access(addresses[i]);
  	 current_time = i + 1; // first access completes at time 1
  }

}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  
  // Overrided << operator for address, so use it
  if(flags.verbose) {
  	cout << address << endl;
  }

  // Get the process corresponding to the given address ("look up" step)
  Process* current_process = processes[address.process_id];
  // Check if the page of the process is present, if not ->page fault
  if(!current_process->page_table.rows[address.page].present) {
  	  handle_page_fault(current_process, address.page);
  }
  // Otherwise, continue
  // Output like Hao's examples
  else {
  	if(flags.verbose) {
  	cout << "\t-> IN MEMORY" << endl;
  	}
  }

  // Get physical address from virtual address
  int virtual_frame = current_process->page_table.rows[address.page].frame;
  int virtual_offset = address.offset;
  PhysicalAddress p_address = PhysicalAddress(virtual_frame, virtual_offset);

  // Output like Hao's examples
  if(flags.verbose) {
  	cout << "\t-> physical address " << p_address << endl;
  	cout << "\t-> RSS: " << current_process->get_rss() << endl;
  }

  current_process->memory_accesses++;
  // Timestamp the page table
  current_process->page_table.rows[address.page].last_accessed_at = current_time;

  if(flags.verbose) {
  	cout << "\t-> byte: " << current_process->pages[address.page]->get_byte_at_offset(virtual_offset) << endl;
  }
  // return the byte at the physical address
  return current_process->pages[address.page]->get_byte_at_offset(virtual_offset);
}


void Simulation::handle_page_fault(Process* process, size_t page) {

  if(flags.verbose) {
  	cout << "\t-> PAGE FAULT" << endl;
  }

  //If we have space, assign the processes frame's to an empty one
  if(flags.max_frames > process->get_rss() && empty_frame_index < flags.max_frames) {
  	process->page_table.rows[page].frame = empty_frame_index;
  	process->page_table.rows[page].loaded_at = current_time;
  	// The conditional makes sure that we can correctly increment our empty frame index
  	empty_frame_index++;
  	// Since we've assigned a frame to the processes' page, we can now say it is present
  	process->page_table.rows[page].present = true;
  }

  // OTHERWISE, replacement strategy time!
  // Replace the least recently used strategy
  else if(flags.strategy == ReplacementStrategy::LRU) {
  	// Get the index of the page that has been least recently used
  	least_recently_used_index = process->page_table.get_least_recently_used_page();
  	// Assign the frame to be replaced index to the frame that this page occupied
  	victim_frame_index = process->page_table.rows[least_recently_used_index].frame;
  	// Remove the page from the frame
  	process->page_table.rows[least_recently_used_index].present = false;
  	process->page_table.rows[least_recently_used_index].frame = NULL;
  	empty_frame_index = victim_frame_index;
  }
  // Replace the oldest strategy
  else if(flags.strategy == ReplacementStrategy::FIFO) {
  	// Get the index of the page that has been least recently used
  	oldest_page_index = process->page_table.get_oldest_page();
  	// Assign the frame to be replaced index to the frame that this page occupied
  	victim_frame_index = process->page_table.rows[oldest_page_index].frame;
  	// Remove the page from the frame
  	process->page_table.rows[oldest_page_index].present = false;
  	process->page_table.rows[oldest_page_index].frame = NULL;
  	empty_frame_index = victim_frame_index;
  }

  // Now that we've cleared a space, put the new page in
  process->page_table.rows[page].frame = empty_frame_index;
  process->page_table.rows[page].present = true;
  process->page_table.rows[page].loaded_at = current_time;
  process->page_faults++;

}

void Simulation::print_results() {
	int total_accesses = 0;
	int total_faults = 0;
	int used_frames = 0; 
	map<int, Process*>::iterator proc_iterator;

	cout << "DONE!" << endl << endl;

	// OUTPUT LIKE WHO, WHAT, WHEN, WHERE AND HAO
	for(proc_iterator = processes.begin(); proc_iterator != processes.end(); proc_iterator++) {
		Process* proc = proc_iterator->second;
		cout << "Process " << proc_iterator->first << ":" 
		<< "\tACCESSES: " << proc->memory_accesses
		<< "\tFAULTS: " << proc->page_faults
		<< "\tFAULT RATE: " << proc->get_fault_percent()
		<< "\tRSS: " << proc->get_rss() << endl;
		total_accesses += proc->memory_accesses;
		total_faults += proc->page_faults;
		used_frames += (proc->get_rss());
	}

	cout << "Total memory accesses:\t\t" << total_accesses << endl;
	cout << "Total page faults:\t\t\t" << total_faults << endl;
	cout << "Free frames remaining:\t\t" << (512 - used_frames) << endl;
}
