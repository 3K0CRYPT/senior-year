//
//  project4.cpp
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"
using namespace std;


// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************

struct ipHdr {
  __u8 ip_hl:4,	ip_v:4;
  __u8 tos;
  __u16 tl;
};

void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

  resultsC* results = (resultsC*)user;
  results->incrementPacketCount();
  TRACE << "Processing packet #" << results->packetCount() << ENDL;
  
  cout << packet[14] << endl;
  
  char *ipHeader = (char *)(packet+14);
  cout << ipHeader[0] << endl;
  
  std::cout <<	ipHeader[2]	<<	std::endl;
  std::cout <<	std::hex	<<	ipHeader[2]	<<	ipHeader[3]	<<	std::endl;
  std::cout <<	std::hex	<<	(u_short)ipHeader[2]	<<	(u_short)ipHeader[3]	<<	std::endl;
  std::cout <<	(ipHeader[2]	<<	8)	+	ipHeader[3]	<<	std::endl;
  
  
  struct ipHdr *	ipHeader =	(struct ipHdr *)(packet	+	14);
  std::cout <<	(int)ipHeader->ip_v <<	std::endl;
  std::cout <<	(int)ipHeader->ip_hl <<	std::endl;
  std::cout <<	ntohs(ipHeader->tl )	<<	std::endl;
    

  return;
}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, char **argv)
{

  // **********************************************************************
  // * Initalize the debugging class.  
  // **********************************************************************
  boost::log::add_console_log(std::cout, boost::log::keywords::format = "%Message%");
  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
  
  // **********************************************************************
  // * The program is called with two arguments:
  // * -f <filename>
  // * -d <debug level>
  // **********************************************************************
  int opt = 0;
  char filename[NAME_MAX];
  while ((opt = getopt(argc,argv,"f:d:")) != -1) {
    
    switch (opt) {
    case 'f':
      strncpy(filename,optarg,NAME_MAX);
      break;
    case 'd':
      if (atoi(optarg) >= 1) boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
      if (atoi(optarg) >= 2) boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
      if (atoi(optarg) >= 3) boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
      break;
    case ':':
    case '?':
    default:
      std::cout << "useage: " << argv[0] << " -f <cpautre file name> -d <debug level>" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  TRACE << "Running project4 on file " << filename << ENDL;
  


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();
  TRACE << "results object created" << ENDL;



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(filename,errbuf)) == NULL ) {
    FATAL << "Unable to open pcap file: " << filename << ENDL;
    exit(EXIT_FAILURE);
  }
  DEBUG << filename << " has been opened." << ENDL;

  if (strlen(errbuf) > 0)
    WARNING << "pcap_open_offiline encountered a non-fatal error: " << pcap_geterr(PT) << ENDL;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  DEBUG << "Calling dispatcher." << ENDL;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    FATAL << "Error calling dispatcher: " << pcap_geterr(PT) << ENDL;
    exit(EXIT_FAILURE);
  }
  DEBUG << "Dispatcher finished with " << pk_count << " packets left in the queue." << ENDL;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}
