/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const { //done
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
