
#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const { 
string frameString, offsetString, address;                                                                                                              
frameString = bitset<10>(frame).to_string();
offsetString = bitset<6>(offset).to_string();
address = frameString + offsetString;
return address;
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
out << address.to_string()
	<< " [frame: " << address.frame
	<< "; offset: " << address.offset
	<< "]";
  return out;
}
