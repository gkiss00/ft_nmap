# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <errno.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <math.h>
# include <stdbool.h>
# include <pcap/pcap.h>
#include <stdio.h>
#include <pcap.h>
#include <netinet/in.h>
#include <net/ethernet.h>

// https://www.devdungeon.com/content/using-libpcap-c?fbclid=IwAR3PkMSBiUnO27QZO1_3Pao8SfrgF0J8tAeOcgw-WIz1_mFDjTpMkI2nVx0#live-capture

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *header,
    const u_char *packet
);

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);


int main() {
    char error[PCAP_ERRBUF_SIZE];
    int res;
    pcap_if_t *all_dev_sp;

    res = pcap_findalldevs(&all_dev_sp, error);
    if(res == PCAP_ERROR) {
        printf("Error on pcap_findalldevs.\n");
        printf("%s", error);
    }

    pcap_if_t *tmp = all_dev_sp;

    int i = 0;
    while(tmp) {
        printf("network_name[%d]: %s\n", i, tmp->name);
        bpf_u_int32 net;
        bpf_u_int32 mask;
        res = pcap_lookupnet(tmp->name, &net, &mask, error);
        if(res < 0) {
            printf("Error on pcap_lookupnet.\n");
            printf("%s", error);
        } else {
            printf("net: %d\nmask: %d\n", net, mask);
        }
        tmp = tmp->next;
        ++i;
    }

    // deprecated
    // char *network = pcap_lookupdev(error);
    // printf("network: %s\n", network);

    bpf_u_int32 net;
    bpf_u_int32 mask;
    res = pcap_lookupnet(all_dev_sp->name, &net, &mask, error);
    if(res < 0) {
        printf("Error on pcap_lookupnet.\n");
        printf("%s", error);
    } else {
        printf("net: %d\nmask: %d\n", net, mask);
    }

    char ip[13];
    char subnet_mask[13];
    struct in_addr address;

    address.s_addr = net;
    strcpy(ip, inet_ntoa(address));
    if (strlen(ip) == 0) {
        printf("Error on inet_ntoa"); /* print error */
        exit(EXIT_FAILURE);
    }
    
    /* Get subnet mask in human readable form */
    address.s_addr = mask;
    strcpy(subnet_mask, inet_ntoa(address));
    if (strlen(subnet_mask) == 0) {
        perror("Error on inet_ntoa");
        exit(EXIT_FAILURE);
    }

    printf("Device: %s\n", all_dev_sp->name);
    printf("IP address: %s\n", ip);
    printf("Subnet mask: %s\n", subnet_mask);

    int packet_count_limit = 1;
    int timeout = 1000; // millisecond

    pcap_t *pcap = pcap_open_live("en1", BUFSIZ, packet_count_limit, timeout, error);
    if(pcap == NULL) {
        printf("Error on pcap_open_live.\n");
        printf("%s", error);
        exit(EXIT_FAILURE);
    }

    const u_char *packet;
    struct pcap_pkthdr packet_header;

    // packet = pcap_next(pcap, &packet_header);
    // if (packet == NULL) {
    //     printf("No packet found.\n");
    //     return 2;
    // }

    // print_packet_info(packet, packet_header);

    pcap_dispatch(pcap, 10, my_packet_handler, NULL);

    //res = pcap_dispatch(pcap, 10, )

    pcap_close(pcap);
    
}

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet
)
{
    struct ether_header *eth_header = (struct ether_header *)packet;

    
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        printf("IP\n");
    } else  if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        printf("ARP\n");
    } else  if (ntohs(eth_header->ether_type) == ETHERTYPE_REVARP) {
        printf("Reverse ARP\n");
    }
    print_packet_info(packet, *packet_header);
    return;
}

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header) {
    printf("Packet capture length: %d\n", packet_header.caplen);
    printf("Packet total length %d\n", packet_header.len);
}