

#pragma once
#include <cstdlib>
#include <vector>



class PageTable {

public:


  PageTable(size_t num_pages) : rows(std::vector<Row>(num_pages)) {}

  size_t get_present_page_count() const;

  size_t get_oldest_page() const;

  size_t get_least_recently_used_page() const;


public:

  struct Row {

    bool present = false;

 
    size_t frame;


    size_t loaded_at = -1;


    size_t last_accessed_at = -1;
  };

  std::vector<Row> rows;
};
