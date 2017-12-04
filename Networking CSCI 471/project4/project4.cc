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


/////////////////////////////////////// Helpers
unsigned short chksum(unsigned short *addr, int len) {
	int nleft = len, sum = 0;
	unsigned short	*w = addr, answer = 0;
	while (nleft > 1)  { sum += *w++; nleft -= 2; }
	if (nleft == 1) { *(unsigned char *)(&answer) = *(unsigned char *)w; sum += answer; }
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return(answer);
}

void printFormat(u_char *toPrint, int iter, char *div, char *fmt) {
    for (int i = 0; i < iter; i++) {
        if (i != 0) printf("%s", div);
        printf(fmt, toPrint[i]);
    }
    printf("\n");
}

void printPort(uint16_t port) {
    switch (port) {
        case 80: printf("HTTP\n"); break;
        case 23: printf("Telnet\n"); break;
        case 21: printf("FTP\n"); break;
        case 110: printf("POP3\n"); break;
        case 25: printf("SMTP\n"); break;
        default: printf("%hu\n", port); break;
    }
}

/* Analyzes UDP segment of the packet */
void UDP(const u_char *packet) {
    headerUDP *head = (headerUDP*)packet;

    printf("\n\tUDP Header\n");
    printf("\t\tSource Port:  ");
    printPort(ntohs(head->portSource));
    printf("\t\tdestination Port:  ");
    printPort(ntohs(head->portDestination));
}

/* Analyzes TCP segment of the packet and performs checksum on
 * the new packet that has the attached pseudoheader */
void TCP(const u_char *packet, uint8_t *_headerIP) {
    headerTCP *head = (headerTCP*)packet;
    headerIP *ip = (headerIP*)_headerIP;
    uint16_t cksum, ret;
    headerPsuedo pseudo;

    /* Create pseudo header */
    memcpy(&(pseudo.s_ip), &(ip->s_ip), sizeof(uint8_t) * IP_ADDRESS_LENGTH);
    memcpy(&(pseudo.d_ip), &(ip->d_ip), sizeof(uint8_t) * IP_ADDRESS_LENGTH);
    memset(&(pseudo.zeros), 0, sizeof(uint8_t));
    pseudo.protocol = ip->protocol;
    pseudo.tcp_len = htons(ntohs(ip->len) - (ip->ver_ihl & IHL_MASK) * 4);

    /* Glue pseudo header to TCP header */
    auto *buff = malloc(sizeof(headerPsuedo) + ntohs(pseudo.tcp_len));
    memcpy(buff, &pseudo, sizeof(headerPsuedo));
    memcpy(buff + sizeof(headerPsuedo), head, ntohs(pseudo.tcp_len));

    printf("\n\tTCP Header\n");
    printf("\t\tSource Port:  ");
    printPort(ntohs(head->portSource));
    printf("\t\tdestination Port:  ");
    printPort(ntohs(head->portDestination));
    printf("\t\tSequence Number: %u\n", ntohl(head->seq));
    printf("\t\tACK Number: %u\n", ntohl(head->ack));
    printf("\t\tSYN Flag: %s\n", head->flags & SYN_MASK ? "Yes" : "No");
    printf("\t\tRST Flag: %s\n", head->flags & RST_MASK ? "Yes" : "No");;
    printf("\t\tFIN Flag: %s\n", head->flags & FIN_MASK ? "Yes" : "No");
    printf("\t\tWindow Size: %hu\n", ntohs(head->win_size));
    printf("\t\tChecksum: ");
    
    cksum = ntohs(head->checksum);
    ret = chksum((uint16_t *)buff, sizeof(headerPsuedo) + ntohs(pseudo.tcp_len));
    if (ret == 0) printf("Correct ");
    else printf("Incorrect ");
    printf("(0x%x)\n", cksum);
}

/* Analyzes ICMP packet */
void ICMP(const u_char *packet) {
    headerICMP *head = (headerICMP*)packet;
    uint8_t type;

    printf("\n\tICMP Header\n");
    printf("\t\tType: ");
    type = head->type;
    if (type == 0) printf("Reply");
    else if (type == 8) printf("Request");
    else printf("Unknown");
}

/* Analyze IP packet and send to appropriate protocol handler */
void IP(const u_char *packet) {
    headerIP *head = (headerIP*)packet;
    uint16_t ret, cksum;
    int type, addtl = 0;

    printf("\tIP Header\n");
    printf("\t\tTOS: 0x%x\n", head->tos);
    printf("\t\tTTL: %u\n", head->ttl);
    
    printf("\t\tProtocol: ");
    type = head->protocol;
    if (type == TYPE_ICMP)  printf("ICMP\n");
    else if (type == TYPE_TCP) printf("TCP\n");
    else if (type == TYPE_UDP) printf("UDP\n");
    else printf("Unknown\n");

    printf("\t\tChecksum: ");
    cksum = ntohs(head->checksum);
    ret = chksum((uint16_t*)head, sizeof(headerIP));
    if (ret == 0) printf("Correct ");
    else printf("Incorrect ");
    printf("(0x%x)\n", cksum);
    
    printf("\t\tSender IP: ");
    printFormat(head->s_ip, IP_ADDRESS_LENGTH, ".", "%d");
    
    printf("\t\tdestination IP: ");
    printFormat(head->d_ip, IP_ADDRESS_LENGTH, ".", "%d");
  
    /* If ihl > 5, must take option length into account */
    if ((head->ver_ihl & IHL_MASK) > 5) addtl = (head->ver_ihl & IHL_MASK);

    uint8_t *_packet = packet;
    
    if (type == TYPE_ICMP) ICMP(packet + IP_SIZE + addtl);
    else if (type == TYPE_TCP) TCP(packet + IP_SIZE + addtl, _packet);
    else if (type == TYPE_UDP) UDP(packet + IP_SIZE + addtl);
}

/* Analyzes ARP packet */
void ARP(const u_char *packet) {
    headerARP *head = (headerARP*)(packet + ARP_OFFSET);

    printf("\tARP header\n");
    printf("\t\tOpcode: ");
    printf(ntohs(head->op) == 1 ? "Request\n" : "Reply\n");
    
    printf("\t\tSender MAC: ");
    printFormat(head->s_mac, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tSender IP: ");
    printFormat(head->s_ip, IP_ADDRESS_LENGTH, ".", "%d");
    
    printf("\t\tTarget MAC: ");
    if (ntohs(head->op) == 1) printf("0:0:0:0:0:0\n");
    else printFormat(head->t_mac, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tTarget IP: ");
    printFormat(head->t_ip, IP_ADDRESS_LENGTH, ".", "%d");
}

/* Takes in the packet off Ethernet and strips it, sending it
 * to the appropraite protocol handlers */
void Ethernet(int count, const struct pcap_pkthdr *header, const u_char *packet) {
    headerETH *head = (headerETH*)packet;
    u_short type;

    printf("\nPacket number: %d  Packet Len: %d\n\n", count, header->len);
    printf("\tEthernet Header\n");
    
    printf("\t\tdestination MAC: ");
    printFormat(head->source, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tSource MAC: ");
    printFormat(head->destination, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tType: ");
    type = ntohs(head->type);
    if (type == TYPE_ARP) {
        printf("ARP\n\n");
        /* Pass data starting after internet header */
        ARP(packet + ETHERNET_SIZE);
    }
    else if (type == TYPE_IP) {
        printf("IP\n\n");
        IP(packet + ETHERNET_SIZE);
    }
    else printf("Unknown\n");
    printf("\n");
}
///////////////////////////////////////

void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

  resultsC* results = (resultsC*)user;
  results->incrementPacketCount();
  TRACE << "Processing packet #" << results->packetCount() << ENDL;
  int count = results->packetCount();
  
  Ethernet(count, pkthdr, packet);
  
  // struct ipHdr *	ipHeader =	(struct ipHdr *)(packet	+	14);
  // std::cout <<	(int)ipHeader->ip_v <<	std::endl;
  // std::cout <<	(int)ipHeader->ip_hl <<	std::endl;
  
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
