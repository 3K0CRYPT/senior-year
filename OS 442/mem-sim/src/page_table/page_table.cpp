/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
	int count = 0;
	for (int i = 0; i < rows.size(); i++){
		if (rows[i].present){
		count++;
		}
		}
  return count;
}


size_t PageTable::get_oldest_page() const {
  int lowest = 69696969;
  int index;
  for(int i = 0; i < rows.size(); i++){
  	if (rows[i].loaded_at < lowest && rows[i].present){
	lowest = rows[i].loaded_at;
	index = i;
	}
  }
  return index;
}


size_t PageTable::get_least_recently_used_page() const {
  int lowest = 69696969;
  int index;
  for(int i = 0; i < rows.size(); i++){
  	if (rows[i].last_accessed_at < lowest && rows[i].present){
	lowest = rows[i].last_accessed_at;
	index = i;
	}
  }
  return index;
}
