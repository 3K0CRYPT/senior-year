
#pragma once
#include "process/process.h"
#include "virtual_address/virtual_address.h"
#include <cstdlib>


class Simulation {

public:


  static const size_t NUM_FRAMES = 1 << 9;


public:

  void run();


private:


  char perform_memory_access(const VirtualAddress& address);

  void handle_page_fault(Process* process, size_t page);


private:

};
