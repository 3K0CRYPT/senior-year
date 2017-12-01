#include "process/process.h"
#include <sstream>
#include <iostream>

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  if(in.peek() == istream::traits_type::eof()) return nullptr;
  istreambuf_iterator<char> eos;
  string s(istreambuf_iterator<char>(in), eos);
 vector<Page*> proc_pages;
for(int i = 0; i < s.size()/Page::PAGE_SIZE +1; i++){
  string ps = s.substr(i*Page::PAGE_SIZE,Page::PAGE_SIZE);
  
  istringstream is(ps);
  Page* p = Page::read_from_input(is);
  proc_pages.push_back(p);
  
}
Process* p = new Process((size_t)s.length(),proc_pages);
  return p;
}


size_t Process::size() const {
	return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  if(pages[index] != NULL)
  return true;

  else return false;
}


size_t Process::get_rss() const {
	size_t presentProcesses =0;
	for(int i = 0; i < page_table.rows.size(); i++){
		if (page_table.rows[i].present){
		presentProcesses++;
		}
	}
  return presentProcesses;
}


double Process::get_fault_percent() const {
	double faultPercent = 0.0;
	if(memory_accesses != 0){
	faultPercent= ((double)page_faults / (double)memory_accesses)*100;}
	return faultPercent;
}
