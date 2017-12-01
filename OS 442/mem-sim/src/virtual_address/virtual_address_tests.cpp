#include "virtual_address/virtual_address.h"
#include "gtest/gtest.h"
#include <bitset>
#include <sstream>

using namespace std;



const int PID = 42;


const string ADDRESS_STRING = "1000100011101010";


const size_t PAGE = bitset<32>("1000100011").to_ulong();
const size_t OFFSET = bitset<32>("101010").to_ulong();


TEST(VirtualAddress, FromString_ProcessId) {
  VirtualAddress address = VirtualAddress::from_string(PID, ADDRESS_STRING);

  ASSERT_EQ(PID, address.process_id);
}


TEST(VirtualAddress, FromString_Page) {
  VirtualAddress address = VirtualAddress::from_string(PID, ADDRESS_STRING);

  ASSERT_EQ(PAGE, address.page);
}


TEST(VirtualAddress, FromString_Offset) {
  VirtualAddress address = VirtualAddress::from_string(PID, ADDRESS_STRING);

  ASSERT_EQ(OFFSET, address.offset);
}


TEST(VirtualAddress, ToString) {
  VirtualAddress address = VirtualAddress::from_string(PID, ADDRESS_STRING);

  ASSERT_EQ(ADDRESS_STRING, address.to_string());
}


TEST(VirtualAddress, OutputOperator) {
  VirtualAddress address = VirtualAddress::from_string(PID, ADDRESS_STRING);
  stringstream expected_output, output;

  
  expected_output
      << "PID " << PID
      << " @ " << ADDRESS_STRING
      << " [page: " << PAGE
      << "; offset: " << OFFSET
      << "]";

  output << address;

  ASSERT_EQ(expected_output.str(), output.str());
}

