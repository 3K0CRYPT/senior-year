#pragma once
#include <cstdlib>
#include <ostream>



class VirtualAddress {

public:


  static const size_t PAGE_BITS = 10;


  static const size_t OFFSET_BITS = 6;

  static const size_t ADDRESS_BITS = PAGE_BITS + OFFSET_BITS;

 
  static const size_t OFFSET_BITMASK = (1 << OFFSET_BITS) - 1;


  static const size_t PAGE_BITMASK = ((1 << PAGE_BITS) - 1) << OFFSET_BITS;


public:


  static VirtualAddress from_string(int process_id, std::string address);


  VirtualAddress(int process_id, int page, int offset)
      : process_id(process_id), page(page), offset(offset) {}

  std::string to_string() const;


public:

  const int process_id;


  const size_t page;

  const size_t offset;
};


std::ostream& operator <<(std::ostream& out, const VirtualAddress& address);
