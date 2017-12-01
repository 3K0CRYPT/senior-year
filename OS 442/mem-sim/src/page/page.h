

#pragma once
#include "virtual_address/virtual_address.h"
#include <cstdlib>
#include <istream>
#include <vector>

class Page {

public:

  static const size_t PAGE_SIZE = 1 << VirtualAddress::OFFSET_BITS;


public:


  static Page* read_from_input(std::istream& in);

  size_t size() const;


  bool is_valid_offset(size_t offset) const;


  char get_byte_at_offset(size_t offset);


private:


  Page(std::vector<char> bytes) : bytes(bytes) {}


private:

  std::vector<char> bytes;
};
