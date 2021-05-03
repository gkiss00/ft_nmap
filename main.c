#include "ft_nmap.h"

t_data data;

int     main(int argc, char **argv) {

    check_error(argc, argv);
    init_data(&data);
    parsing(&data, argv);
    exit(EXIT_SUCCESS);
}