#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>
#include "checksum.h"
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>

#define TYPE_ARP 0x0806
#define TYPE_IP 0x0800
#define TYPE_TCP 0x06
#define TYPE_ICMP 0x01
#define TYPE_UDP 0x11

#define ETHER_SIZE 14
#define ETHERNET_ADDRESS_LENGTH 6

#define IP_SIZE 20
#define IP_ADDRESS_LENGTH 4

#define ARP_SIZE 28
#define ARP_OFFSET 6

#define FIN_MASK 0x1
#define SYN_MASK 0x2
#define RST_MASK 0x4
#define IHL_MASK 0xf

 struct headerETH {
    uint8_t source[ETHERNET_ADDRESS_LENGTH], destination[ETHERNET_ADDRESS_LENGTH];
    uint16_t type;
};
 struct headerARP {
    uint8_t s_mac[ETHERNET_ADDRESS_LENGTH], s_ip[IP_ADDRESS_LENGTH], t_mac[ETHERNET_ADDRESS_LENGTH], t_ip[IP_ADDRESS_LENGTH];
    uint16_t op;
};
 struct headerIP {
    uint8_t ver_ihl, tos, ttl, protocol, s_ip[IP_ADDRESS_LENGTH], d_ip[IP_ADDRESS_LENGTH];
    uint16_t len, id, flags_frag, checksum;
};
 struct headerUDP { uint16_t portSource, portDestination; };
 struct headerICMP { uint8_t type; };
 struct headerTCP {
    uint8_t offset, flags;
    uint16_t portSource, portDestination, win_size, checksum;
    uint32_t seq, ack;
};
 struct headerPsuedo {
    uint8_t s_ip[IP_ADDRESS_LENGTH], d_ip[IP_ADDRESS_LENGTH], zeros, protocol;               
    uint16_t tcp_len;
};
