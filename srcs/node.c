#include "./../ft_nmap.h"

t_node *new_node() {
    t_node *node;

    node = malloc(sizeof(t_node));
    node->next = NULL;
    return (node);
}

t_node *node_last(t_node *node) {
    while (node && node->next) {
        node = node->next;
    }
    return (node);
}

void node_add_back(t_node **head, t_node *new) {
    if (head != 0)
	{
		if (*head && new != 0)
		{
			node_last(*head)->next = new;
		}
		else
		{
			*head = new;
		}
	}
}

void free_node(t_node *port) {
    t_node *tmp = port;

    while(port) {
        tmp = port->next;
        free(port);
        port = tmp;
    }
}

t_scan *new_scan(char *type) {
    t_scan *node;

    node = malloc(sizeof(t_scan));
    node->type = strdup(type);
    node->next = NULL;
    return (node);
}

t_scan *scan_last(t_scan *node) {
    while (node && node->next) {
        node = node->next;
    }
    return (node);
}

void scan_add_back(t_scan **head, t_scan *new) {
    if (head != 0)
	{
		if (*head && new != 0)
		{
			scan_last(*head)->next = new;
		}
		else
		{
			*head = new;
		}
	}
}

void free_scan(t_scan *port) {
    t_scan *tmp = port;

    while(port) {
        tmp = port->next;
        free(port->type);
        free(port);
        port = tmp;
    }
}

t_port *new_port(int min, int max) {
    t_port *node;

    node = malloc(sizeof(t_port));
    node->min = min;
    node->max = max;
    node->next = NULL;
    return (node);
}

t_port *port_last(t_port *node) {
    while (node && node->next) {
        node = node->next;
    }
    return (node);
}

void port_add_back(t_port **head, t_port *new) {
    if (head != 0)
	{
		if (*head && new != 0)
		{
			port_last(*head)->next = new;
		}
		else
		{
			*head = new;
		}
	}
}

void free_port(t_port *port) {
    t_port *tmp = port;

    while(port) {
        tmp = port->next;
        free(port);
        port = tmp;
    }
}

t_target *new_target(char *target) {
    t_target *node;

    node = malloc(sizeof(t_target));
    node->target = strdup(target);
    node->next = NULL;
    return (node);
}

t_target *target_last(t_target *node) {
    while (node && node->next) {
        node = node->next;
    }
    return (node);
}

void target_add_back(t_target **head, t_target *new) {
    if (head != 0)
	{
		if (*head && new != 0)
		{
			target_last(*head)->next = new;
		}
		else
		{
			*head = new;
		}
	}
}

void free_target(t_target *port) {
    t_target *tmp = port;

    while(port) {
        tmp = port->next;
        free(port->target);
        free(port);
        port = tmp;
    }
}