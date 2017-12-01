#include "virtual_address/virtual_address.h"
#include <sstream>
#include <iostream>
#include <bitset>

using namespace std;

VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  int offset = stoi(address.substr(10,6),nullptr,2), page = stoi(address.substr(0,10),nullptr,2);
  VirtualAddress virtaddress (process_id, page, offset);
  return virtaddress;
}

string VirtualAddress::to_string() const {  return bitset<10>(page).to_string() + bitset<6>(offset).to_string(); }


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out << "PID " << address.process_id << " @ " << address.to_string() << " [page: " << address.page << "; offset: " << address.offset << "]";
  return out;
}
