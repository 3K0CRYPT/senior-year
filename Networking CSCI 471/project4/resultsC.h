//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//
#pragma once

#ifndef resultsC_h
#define resultsC_h

#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>
#include "checksum.h"
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>
#include <map>
#include <vector>


#define TYPE_ARP 0x0806
#define TYPE_IP 0x0800
#define TYPE_TCP 0x06
#define TYPE_ICMP 0x01
#define TYPE_UDP 0x11

#define ETHERNET_SIZE 14
#define ETHERNET_ADDRESS_LENGTH 6

#define IP_SIZE 20
#define IP_ADDRESS_LENGTH 4

#define ARP_SIZE 28
#define ARP_OFFSET 6

#define FIN_MASK 0x1
#define SYN_MASK 0x2
#define RST_MASK 0x4
#define IHL_MASK 0xf

 typedef struct {
    uint8_t source[ETHERNET_ADDRESS_LENGTH], destination[ETHERNET_ADDRESS_LENGTH];
    uint16_t type;
} headerETH;
 typedef struct {
    uint8_t s_mac[ETHERNET_ADDRESS_LENGTH], s_ip[IP_ADDRESS_LENGTH], t_mac[ETHERNET_ADDRESS_LENGTH], t_ip[IP_ADDRESS_LENGTH];
    uint16_t op;
} headerARP;
 typedef struct {
    uint8_t ver_ihl, tos, ttl, protocol, s_ip[IP_ADDRESS_LENGTH], d_ip[IP_ADDRESS_LENGTH];
    uint16_t len, id, flags_frag, checksum;
} headerIP;
 typedef struct { uint16_t portSource, portDestination; } headerUDP;
 typedef struct { uint8_t type; } headerICMP;
 typedef struct {
    uint8_t offset, flags;
    uint16_t portSource, portDestination, win_size, checksum;
    uint32_t seq, ack;
} headerTCP;
 typedef struct {
    uint8_t s_ip[IP_ADDRESS_LENGTH], d_ip[IP_ADDRESS_LENGTH], zeros, protocol;
    uint16_t tcp_len;
} headerPsuedo;


class resultsC {
  protected:
   int totalPacketCount;

  public:
   resultsC();
   void incrementTotalPacketCount() { totalPacketCount++; };
   void displayResults();
   int packetCount() { return totalPacketCount; };
   unsigned int arp=0;
   unsigned int ipv4=0;
   unsigned int ipv6=0;
   unsigned int other=0;
   unsigned int icmp=0;
   unsigned int udp=0;
   unsigned int tcp=0;
   unsigned int syn=0;
   unsigned int fin=0;
   unsigned int frags=0;
   unsigned int checks=0;
   std::vector<int> ipv4l = {0};
   std::vector<int> ipv6l = {0};
   std::map<std::string, bool> macs;
   std::map<std::string, bool> ips;
   std::map<std::string, bool> udport;
   std::map<std::string, bool> tcport;
};

#endif
