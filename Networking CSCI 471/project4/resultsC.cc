//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

// ***************************************************************************
// * resultsC::resultsC
// *  Constructor for the results container class.  
// ***************************************************************************
resultsC::resultsC() {
  totalPacketCount = 0;
}


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {
  std::cout << "\nA total of " << totalPacketCount << " packets processed." << std::endl;
  std::cout << "ARPs: " << arp << "\nIPv4: " << ipv4 << "\nOther types: " << other 
  << "\nICMP: "<< icmp <<"\nUDP: " << udp << "\nTCP: " << tcp << "\nSYNs: " << syn << "\nFINs: " << fin;
  int nmac=0, nip=0, nup=0, ntp=0;
  for (auto p: macs) nmac++;
  for (auto p: ips) nip++;
  for (auto p: udport) nup++;
  for (auto p: tcport) ntp++;
  std::cout << "\nMACs: " << nmac << "\nIPs: " << nip << "\nUDP ports: " << nup << "\nTCP ports: " << ntp << std::endl;
}
