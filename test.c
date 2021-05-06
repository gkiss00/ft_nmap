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

int main() {
    char error[256];
    pcap_if_t **all_dev_sp;
    all_dev_sp = malloc(1000);
    int res = pcap_findalldevs(all_dev_sp, error);

    pcap_if_t *tmp = *all_dev_sp;

    int i = 0;
    while(tmp) {
        printf("network_name[%d]: %s\n", i, tmp->name);
        tmp = tmp->next;
        ++i;
    }
    
}