

#pragma once
#include "page/page.h"
#include "process/process.h"

class Frame {

public:

  void set_page(Process* process, size_t page_number);


public:


  Page* contents = nullptr;


  size_t page_number;


  Process* process = nullptr;
};
