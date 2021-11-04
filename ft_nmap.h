#ifndef FT_NMAP_H
#define FT_NMAP_H

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
# include <pcap.h>
# include <netinet/if_ether.h>

typedef struct          s_target
{
    char                *target;
    struct s_target     *next;
}                       t_target;

typedef struct          s_scan
{
    char                *type;
    struct s_scan       *next;
}                       t_scan;

typedef struct          s_port
{
    int                 min;
    int                 max;
    struct s_port       *next;
}                       t_port;

typedef struct          s_node
{
    struct s_node       *next;
}                       t_node;

typedef struct          s_option
{
    int                 h; // ???
}                       t_option;

typedef struct		    s_data
{
    char                address[100];
    int                 nb_thread;
    struct s_port       *port;
    struct s_scan       *scan;
    struct s_target     *target;
}                       t_data;

// CHAIN BLOCK
t_node *new_node();
t_node *node_last(t_node *node);
void node_add_back(t_node **head, t_node *new);
void free_node(t_node *port);

t_scan *new_scan(char *type);
t_scan *scan_last(t_scan *node);
void scan_add_back(t_scan **head, t_scan *new);
void free_scan(t_scan *port);

t_port *new_port(int min, int max);
t_port *port_last(t_port *node);
void port_add_back(t_port **head, t_port *new);
void free_port(t_port *port);

t_target *new_target(char *type);
t_target *target_last(t_target *node);
void target_add_back(t_target **head, t_target *new);
void free_target(t_target *port);

// ERROR
void check_error(int argc, char **argv);

// PARSING
void parsing(t_data *data, char **argv);

// INIT DATA
void init_data(t_data *data);

// UTILS
char **ft_split(const char *str, char charset);
int tab_length(char **tab);
void free_tab(char **tab);
char *ft_strjoin(char *s1, char *s2);

#endif