/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"

using namespace std;


string PhysicalAddress::to_string() const {

	string _string = string(FRAME_BITS + OFFSET_BITS, '0');
	int temp_frame = this->frame;
	int temp_offset = this->offset;

	// There's gotta be an easier way to do this
	// F it, we'll do it live
	for(int i = 0; i < FRAME_BITS; i++) {
		if(temp_frame % 2 == 1) {
			_string[FRAME_BITS - 1 - i] = '1';
		}
		temp_frame /= 2;
	}
	for(int i = 0; i < OFFSET_BITS; i++) {
		if(temp_offset % 2 == 1) {
			_string[FRAME_BITS + OFFSET_BITS - 1 - i] = '1';
		}
		temp_offset /= 2;
	}
  return _string;
}


//"0010100011111010 [frame: 163; offset: 58]"
ostream& operator <<(ostream& out, const PhysicalAddress& address) {
	out << address.to_string() << " [frame: " << address.frame
	<< "; offset: " << address.offset << "]";
  return out;
}
