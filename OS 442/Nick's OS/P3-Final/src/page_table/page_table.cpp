/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
  // TODO: implement me
  size_t count = 0;
  for(int i = 0; i < rows.size(); i++) {
  	// only count page if it is in main memory
  	if(rows[i].present) {
  		count++;
  	}
  }
  return count;
}


size_t PageTable::get_oldest_page() const {
  // TODO: implement me
  size_t oldest_page_index = 0;
  size_t loaded_time = 32000; // some big int guaranteed to be replaced
  for(size_t i = 0; i < rows.size(); i++) {
  	// only count page if it is in main memory
  	if(rows[i].present && (rows[i].loaded_at < loaded_time)) {
       loaded_time = rows[i].loaded_at;
       oldest_page_index = i;
  	}
  }
  return oldest_page_index;
}


size_t PageTable::get_least_recently_used_page() const {
  // TODO: implement me
  size_t recent_page_index = 0;
  size_t accessed_time = -1; // int guaranteed to be replaced
  for(size_t i = 0; i < rows.size(); i++) {
  	// only count page if it is in main memory
  	if(rows[i].present && (rows[i].last_accessed_at < accessed_time)) {
       accessed_time = rows[i].last_accessed_at;
       recent_page_index = i;
  	}
  }
  return recent_page_index;
}
