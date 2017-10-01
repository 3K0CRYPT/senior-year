/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  // TODO: implement me
  int index = 0;
  in.seekg(0, ios::end);
  // move stream to end character
  int size = in.tellg();
  // Get the position of the stream, at the last character
  in.seekg(0, ios::beg);
  // move us back to the beginning of the stream;
  vector<Page*> pages;
  while (in.peek() != EOF) {
    index++;
    pages.push_back(Page::read_from_input(in));
  }
  if (index == 0) { return nullptr; }
  return new Process(size, pages);
}


size_t Process::size() const {
  // TODO: implement me
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  // TODO: implement me
  return (index <= pages.size() - 1);
}


size_t Process::get_rss() const {
  // TODO: implement me
  return page_table.get_present_page_count();
}

double Process::get_fault_percent() const {
  // TODO: implement me
  if(!memory_accesses) {
    // can't have a fault if we haven't requested anything
    return 0.0;
  }
  else {
    return (100.0*page_faults)/ (1.0*memory_accesses);
  }
}
