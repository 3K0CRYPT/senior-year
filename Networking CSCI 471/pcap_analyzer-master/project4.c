#include "project4.h"

unsigned short in_cksum(unsigned short *addr, int len) {
	int				nleft = len, sum = 0;
	unsigned short	*w = addr, answer = 0;
	while (nleft > 1)  { sum += *w++; nleft -= 2; }
	if (nleft == 1) { *(unsigned char *)(&answer) = *(unsigned char *)w; sum += answer; }
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return(answer);
}

void fmt_print(u_char *toPrint, int iter, char *div, char *fmt) {
    for (int i = 0; i < iter; i++) {
        if (i != 0) printf("%s", div);
        printf(fmt, toPrint[i]);
    }
    printf("\n");
}

/* Printing utility for known ports */
void print_port(uint16_t port) {
    switch (port) {
        case 80:
            printf("HTTP\n");
            break;
        case 23:
            printf("Telnet\n");
            break;
        case 21:
            printf("FTP\n");
            break;
        case 110:
            printf("POP3\n");
            break;
        case 25:
            printf("SMTP\n");
            break;
        default:
            printf("%hu\n", port);
            break;
    }
}

/* Analyzes UDP segment of the packet */
void udp(uint8_t *packet)
{
    headerUDP *head = (headerUDP*)packet;

    printf("\n\tUDP Header\n");
    printf("\t\tSource Port:  ");
    print_port(ntohs(head->portSource));
    printf("\t\tdestination Port:  ");
    print_port(ntohs(head->portDestination));
}

/* Analyzes TCP segment of the packet and performs checksum on
 * the new packet that has the attached pseudoheader */
void tcp(uint8_t *packet, uint8_t *headerIP)
{
    headerTCP *head = (headerTCP*)packet;
    headerIP *ip = (headerIP*)headerIP;
    uint16_t cksum, ret;
    headerPsuedo pseudo;

    /* Create pseudo header */
    memcpy(&(pseudo.s_ip), &(ip->s_ip), sizeof(uint8_t) * IP_ADDRESS_LENGTH);
    memcpy(&(pseudo.d_ip), &(ip->d_ip), sizeof(uint8_t) * IP_ADDRESS_LENGTH);
    memset(&(pseudo.zeros), 0, sizeof(uint8_t));
    pseudo.protocol = ip->protocol;
    pseudo.tcp_len = htons(ntohs(ip->len) - (ip->ver_ihl & IHL_MASK) * 4);

    /* Glue pseudo header to tcp header */
    uint8_t *buff = malloc(sizeof(headerPsuedo) + ntohs(pseudo.tcp_len));
    memcpy(buff, &pseudo, sizeof(headerPsuedo));
    memcpy(buff + sizeof(headerPsuedo), head, ntohs(pseudo.tcp_len));

    printf("\n\tTCP Header\n");
    printf("\t\tSource Port:  ");
    print_port(ntohs(head->portSource));
    printf("\t\tdestination Port:  ");
    print_port(ntohs(head->portDestination));
    printf("\t\tSequence Number: %u\n", ntohl(head->seq));
    printf("\t\tACK Number: %u\n", ntohl(head->ack));
    printf("\t\tSYN Flag: %s\n", head->flags & SYN_MASK ? "Yes" : "No");
    printf("\t\tRST Flag: %s\n", head->flags & RST_MASK ? "Yes" : "No");;
    printf("\t\tFIN Flag: %s\n", head->flags & FIN_MASK ? "Yes" : "No");
    printf("\t\tWindow Size: %hu\n", ntohs(head->win_size));
    printf("\t\tChecksum: ");
    
    cksum = ntohs(head->checksum);
    ret = in_cksum((uint16_t *)buff, sizeof(headerPsuedo) +
            ntohs(pseudo.tcp_len));
    if (ret == 0)
        printf("Correct ");
    else
        printf("Incorrect ");
    printf("(0x%x)\n", cksum);
}

/* Analyzes ICMP packet */
void icmp(uint8_t *packet)
{
    headerICMP *head = (headerICMP*)packet;
    uint8_t type;

    printf("\n\tICMP Header\n");
    printf("\t\tType: ");
    type = head->type;
    if (type == 0)
        printf("Reply");
    else if (type == 8)
        printf("Request");
    else
        printf("Unknown");
}

/* Analyze IP packet and send to appropriate protocol handler */
void ip(uint8_t *packet)
{
    headerIP *head = (headerIP*)packet;
    uint16_t ret, cksum;
    int type, addtl = 0;

    printf("\tIP Header\n");
    printf("\t\tTOS: 0x%x\n", head->tos);
    printf("\t\tTTL: %u\n", head->ttl);
    
    printf("\t\tProtocol: ");
    type = head->protocol;
    if (type == TYPE_ICMP)
        printf("ICMP\n");
    else if (type == TYPE_TCP)
        printf("TCP\n");
    else if (type == TYPE_UDP)
        printf("UDP\n");
    else
        printf("Unknown\n");

    printf("\t\tChecksum: ");
    cksum = ntohs(head->checksum);
    ret = in_cksum((uint16_t*)head, sizeof(headerIP));
    if (ret == 0)
        printf("Correct ");
    else
        printf("Incorrect ");
    printf("(0x%x)\n", cksum);
    
    printf("\t\tSender IP: ");
    fmt_print(head->s_ip, IP_ADDRESS_LENGTH, ".", "%d");
    
    printf("\t\tdestination IP: ");
    fmt_print(head->d_ip, IP_ADDRESS_LENGTH, ".", "%d");
  
    /* If ihl > 5, must take option length into account */
    if ((head->ver_ihl & IHL_MASK) > 5)
        addtl = (head->ver_ihl & IHL_MASK);

    if (type == TYPE_ICMP)
        icmp(packet + IP_SIZE + addtl);
    else if (type == TYPE_TCP)
        tcp(packet + IP_SIZE + addtl, packet);
    else if (type == TYPE_UDP)
        udp(packet + IP_SIZE + addtl);
}

/* Analyzes ARP packet */
void arp(uint8_t *packet)
{
    headerARP *head = (headerARP*)(packet + ARP_OFFSET);

    printf("\tARP header\n");
    printf("\t\tOpcode: ");
    printf(ntohs(head->op) == 1 ? "Request\n" : "Reply\n");
    
    printf("\t\tSender MAC: ");
    fmt_print(head->s_mac, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tSender IP: ");
    fmt_print(head->s_ip, IP_ADDRESS_LENGTH, ".", "%d");
    
    printf("\t\tTarget MAC: ");
    if (ntohs(head->op) == 1)
        printf("0:0:0:0:0:0\n");
    else
        fmt_print(head->t_mac, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tTarget IP: ");
    fmt_print(head->t_ip, IP_ADDRESS_LENGTH, ".", "%d");
}

/* Takes in the packet off ethernet and strips it, sending it
 * to the appropraite protocol handlers */
void ethernet(int count, struct pcap_pkthdr *header, uint8_t *packet)
{
    headerETH *head = (headerETH*)packet;
    u_short type;

    printf("\nPacket number: %d  Packet Len: %d\n\n", count, header->len);
    printf("\tEthernet Header\n");
    
    printf("\t\tdestination MAC: ");
    fmt_print(head->source, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tSource MAC: ");
    fmt_print(head->destination, ETHERNET_ADDRESS_LENGTH, ":", "%x");
    
    printf("\t\tType: ");
    type = ntohs(head->type);
    if (type == TYPE_ARP) {
        printf("ARP\n\n");
        /* Pass data starting after internet header */
        arp(packet + ETHER_SIZE);
    }
    else if (type == TYPE_IP) {
        printf("IP\n\n");
        ip(packet + ETHER_SIZE);
    }
    else {
        printf("Unknown\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;
    uint8_t *packet;
    int count = 0, stat;

    if (argc != 2) {
        perror("Error: Invalid argument count. Usage: trace <pcap>\n");
        exit(EXIT_FAILURE);
    }

    handle = pcap_open_offline(argv[1], errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Failed to open pcap file:\n\t%s\n", errbuf);
        exit(EXIT_FAILURE);
    }

    /* -2 means nothing more to be read */
    while ((stat = pcap_next_ex(handle, &header,
                    (const u_char**)&packet)) != -2) {
        /* -1 indicates error */
        if (stat == -1) {
            pcap_perror(handle, "Error reading packets");
            exit(EXIT_FAILURE);
        }
        
        ethernet(++count, header, packet);
    }

    pcap_close(handle);
    return 0;
}
