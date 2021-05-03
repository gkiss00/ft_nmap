#include "./../ft_nmap.h"

static void get_file(t_data *data, char *arg) {
    int fd = open(arg, O_RDONLY);
    int ret = 0;
    char buff[2];
    char *tmp = NULL;

    while((ret = read(fd, buff, 1)) > 0) {
        buff[ret] = '\0';
        if(buff[0] == '\n') {
            target_add_back(&data->target, new_target(tmp));
            free(tmp);
            tmp = NULL;
        } else {
            tmp = ft_strjoin(tmp, buff);
        }
    }
    target_add_back(&data->target, new_target(tmp));
}

static void get_nb_thread(t_data *data, char *arg) {
    data->nb_thread = atoi(arg);
}

static void get_scan(t_data *data, char *arg) {
    char **tab = ft_split(arg, '/');
    int i = 0;

    free_scan(data->scan);
    data->scan = NULL;
    while(tab[i]) {
        scan_add_back(&data->scan, new_scan(tab[i]));
        ++i;
    }
    free_tab(tab);
}

static void get_port(t_data *data, char *arg) {
    char **tab = ft_split(arg, ',');
    int i = 0;

    free_port(data->port);
    data->port = NULL;
    while(tab[i]) {
        char **tmp= ft_split(tab[i], '-');

        if (tab_length(tmp) == 1) {
            port_add_back(&data->port, new_port(atoi(tmp[0]), atoi(tmp[0])));
        } else if (tab_length(tmp) == 2) {
            port_add_back(&data->port, new_port(atoi(tmp[0]), atoi(tmp[1])));
        }
        free_tab(tmp);
        ++i;
    }
    free_tab(tab);
}

static void get_target(t_data *data, char *arg) {
    target_add_back(&data->target, new_target(arg));
}

void parsing(t_data *data, char **argv) {
    int i = 1;

    while(argv[i]) {
        if (strcmp(argv[i], "--ip") == 0) {
            get_target(data, argv[i + 1]);
        } else if (strcmp(argv[i], "--scan") == 0) {
            get_scan(data, argv[i + 1]);
        } else if (strcmp(argv[i], "--port") == 0) {
            get_port(data, argv[i + 1]);
        } else if (strcmp(argv[i], "--speedup") == 0) {
            get_nb_thread(data, argv[i + 1]);
        } else if (strcmp(argv[i], "--file") == 0) {
            get_file(data, argv[i + 1]);
        }
        ++i;
    }
}