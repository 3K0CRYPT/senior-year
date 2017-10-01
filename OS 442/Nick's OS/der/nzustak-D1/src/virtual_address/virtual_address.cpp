/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

 #include "virtual_address/virtual_address.h"
 #pragma once
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>       /* pow */

 using namespace std;


 VirtualAddress VirtualAddress::from_string(int process_id, string address) {
   // TODO: implement me
   // Yes I'm sure there's a better way to do this, using bitwise operations

   int _page = 0;
   int _offset = 0;
   for(int i = 0; i < PAGE_BITS; i++) {
   	if(address[i] == '1')
     _page += (int) pow(2.0, (double) (PAGE_BITS - i - 1));
   }
   for(int i = 0; i < OFFSET_BITS; i++) {
   	if(address[PAGE_BITS + i] == '1')
     _offset += (int) pow(2.0, (double) (OFFSET_BITS - i - 1));
   }
   return VirtualAddress(process_id, _page, _offset);
 }


 string VirtualAddress::to_string() const {
   // TODO: implement me
 	string _string = string(PAGE_BITS + OFFSET_BITS, '0');
 	int temp_page = this->page;
 	int temp_offset = this->offset;
 	for(int i = 0; i < PAGE_BITS; i++) {
 		if(temp_page % 2 == 1) {
 			_string[PAGE_BITS - 1 - i] = '1';
 		}
 		temp_page /= 2;
 	}
 	for(int i = 0; i < OFFSET_BITS; i++) {
 		if(temp_offset % 2 == 1) {
 			_string[PAGE_BITS + OFFSET_BITS - 1 - i] = '1';
 		}
 		temp_offset /= 2;
 	}
   return _string;
 }


 ostream& operator <<(ostream& out, const VirtualAddress& address) {
   // TODO: implement me
 	out << "PID " << address.process_id << " @ " << address.to_string()
 	<< " [page: " << address.page << "; offset: " << address.offset << "]";
   return out;
 }
