#include "./../ft_nmap.h"

static void set_ports(t_data *data) {
    port_add_back(&data->port, new_port(1, 1024));
}

static void set_scans(t_data *data) {
    char scans[6][5] = {"SYN", "NULL", "ACK", "FIN", "XMAS", "UDP"};
    for (int i = 0; i < 6; ++i) {
        scan_add_back(&data->scan, new_scan(scans[i]));
    }
}

void init_data(t_data *data) {
    data->nb_thread = 0;
    data->port = NULL;
    data->scan = NULL;
    data->target = NULL;
    set_scans(data);
    set_ports(data);
}