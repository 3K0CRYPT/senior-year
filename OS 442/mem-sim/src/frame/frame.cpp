#include "frame/frame.h"

using namespace std;


void Frame::set_page(Process* process, size_t page_number) {
  
  this->process=process;
  this->page_number = page_number;
  this->contents = process->pages[page_number];
}
