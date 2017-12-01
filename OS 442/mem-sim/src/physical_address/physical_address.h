

#pragma once
#include "virtual_address/virtual_address.h"
#include <cstdlib>
#include <ostream>



class PhysicalAddress {

public:

 
  static const size_t FRAME_BITS = 10;


  static const size_t OFFSET_BITS = VirtualAddress::OFFSET_BITS;


  static const size_t ADDRESS_BITS = FRAME_BITS + OFFSET_BITS;


public:

  PhysicalAddress(int frame, int offset) : frame(frame), offset(offset) {}

  std::string to_string() const;


public:


  const int frame;

  const int offset;
};


std::ostream& operator <<(std::ostream& out, const PhysicalAddress& address);
