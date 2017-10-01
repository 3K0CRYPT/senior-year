/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"
#include <iostream>

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  // TODO: implement me
  // int c = in.peek();  // peek character
  // if(c == EOF)
  // 	return nullptr;
  // char * buffer = new char [Page::PAGE_SIZE];
  // in.read(buffer, Page::PAGE_SIZE);
  // vector<char> data(buffer, buffer + Page::PAGE_SIZE);
  // return new Page(data);
  int ctr = 0;
  vector<char> data;
  Page* pptr;
  while((in.peek() != EOF) && ctr < PAGE_SIZE) {
  	//cout << "got " << in.peek() << endl;
  	data.push_back(in.get());
  	ctr++;
  }
  //cout << "Size is " << data.size() << endl;
  if(data.empty()) {
  	//cout << "Empty istream" << endl;
  	pptr = nullptr;
  }
  else {
  	pptr = new Page(data);
  }
  return pptr;
}


size_t Page::size() const {
  // TODO: implement me
  return bytes.size(); 
}


bool Page::is_valid_offset(size_t offset) const {
  // TODO: implement me
   if (bytes.empty() || (offset >= bytes.size())) {
        return false;
    }
    else {
        return true;
    }
}


char Page::get_byte_at_offset(size_t offset) {
  // TODO: implement me
  if(is_valid_offset(offset)) {
  	return bytes.at(offset);
  }
  else {
  	return NULL;
  }
}
