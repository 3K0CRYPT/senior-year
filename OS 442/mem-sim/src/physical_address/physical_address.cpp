#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;

string PhysicalAddress::to_string() const { return bitset<10>(frame).to_string() + bitset<6>(offset).to_string(); }

ostream& operator <<(ostream& out, const PhysicalAddress& address) {
	out << address.to_string() << " [frame: " << address.frame << "; offset: " <<  address.offset << "]";
	return out;
}
