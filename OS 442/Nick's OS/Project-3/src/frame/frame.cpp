/**
 * This file contains implementations for methods in the Frame class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "frame/frame.h"

using namespace std;


void Frame::set_page(Process* process, size_t page_number) {
  // TODO: implement me
	// swap out the old process for the new 
	if(this->process != nullptr) {
		// Simulate moving the process out of main memory
		this->process->page_table.rows[this->page_number].present = false;
	}
	// Bring in the new process into "main memory"
	process->page_table.rows[page_number].present = true;
	// Now make the frame reflect our new process's presence
	this->page_number = page_number;
	this->process = process;
	// And bring in the page-specific contents to the frame
	this->contents = process->pages[page_number];
}
