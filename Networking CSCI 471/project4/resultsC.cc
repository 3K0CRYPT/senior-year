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
  std::cout << "                             \n";
  std::cout << "                             \n";
  
  std::cout << "\nA total of " << totalPacketCount << " packets processed." << std::endl;
  int nmac=0, nip=0, nup=0, ntp=0, v4max=0,v4min=99999,v4avg=0, v6max=0,v6min=99999,v6avg=0;
  for (auto p: macs) nmac++;
  for (auto p: ips) nip++;
  for (auto p: udport) nup++;
  for (auto p: tcport) ntp++;
  
  for (int len: ipv4l) {
    v4max = len > v4max ? len : v4max;
    v4min = len < v4min ? len : v4min;
    v4avg += len;
  }
  v4avg /= ipv4l.size();
  
  std::cout << "ARPs: " << arp;
  if (arp) std::cout << ", Max Length: 60, Min Length: 60, Avg Length: 60";
  if (ipv4l.size()) std::cout << "\nIPv4's: " << ipv4 << ", Max Length: " << v4max << ", Min Length: " << v4min << ", Avg Length: " << v4min;
  if (ipv6l.size()) std::cout << "\nIPv6: " << ipv6 << ", Max Length: " << v6max << ", Min Length: " << v6min << ", Avg Length: " << v6min;
  std::cout << "\nOther types: " << other << "\nICMP: "<< icmp <<"\nUDP: " << udp << "\nTCP: " << tcp << "\nSYNs: " << syn << "\nFINs: " << fin << "\nFrags: " << frags;
  std::cout << "\nMACs: " << nmac << "\nIPs: " << nip << "\nUDP ports: " << nup << "\nTCP ports: " << ntp << "\nCorrect Checksums: " << checks << std::endl;
}
