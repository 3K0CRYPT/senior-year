
#pragma once
#include "page/page.h"
#include "page_table/page_table.h"
#include <vector>
#include <istream>



class Process {

public:


  static Process* read_from_input(std::istream& in);


  size_t size() const;


  bool is_valid_page(size_t index) const;


  size_t get_rss() const;


  double get_fault_percent() const;


private:


  Process(size_t num_bytes, std::vector<Page*> pages)
      : num_bytes(num_bytes),
        pages(pages),
        page_table(PageTable(pages.size())) {}


public:


  const size_t num_bytes;

  const std::vector<Page*> pages;

  PageTable page_table;


  size_t memory_accesses = 0;

  size_t page_faults = 0;
};
