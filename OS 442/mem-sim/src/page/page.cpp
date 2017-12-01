#include "page/page.h"
#include <iostream>
#include <string.h>

using namespace std;



const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  if(in.peek() == istream::traits_type::eof()) return nullptr;
  istreambuf_iterator<char> eos;
  string s(istreambuf_iterator<char>(in), eos);
  vector<char> bytes;
  if(s.size() > PAGE_SIZE){
  for(int i = 0; i < PAGE_SIZE; i++){
	  if(s[i] == '\0'){
	  bytes.push_back('\0');
	  }
  	bytes.push_back(s[i]);
  }
  }
  else {
  	for(int j = 0; j < s.size(); j++){
  		bytes.push_back(s[j]);
	}
  }
  Page* p = new Page(bytes);
  return p;
}


size_t Page::size() const {
  return this->bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  if((size() > offset) && size() != 0) return true;
  else return false;
}


char Page::get_byte_at_offset(size_t offset) { 
	size_t sizer = size();

  if(is_valid_offset(offset)){
  	return this->Page::bytes.at(offset);}
  else return 0;
}
