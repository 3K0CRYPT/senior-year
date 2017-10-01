/**
 * This file contains implementations for methods in the Frame class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "frame/frame.h"

using namespace std;


void Frame::set_page(Process* p, size_t p_num) {
  // TODO: implement me
  // swap out the old process for the new
  if(process != nullptr) {
		// Simulate moving the process out of main memory
		process->page_table.rows[page_number].present = false;
	}
  // Bring in the new process into "main memory"
	p->page_table.rows[p_num].present = true;
  // Now make the frame reflect our new process's presence
	page_number = p_num;
	process = p;
	// And bring in the page-specific contents to the frame
	contents = p->pages[p_num];
}
