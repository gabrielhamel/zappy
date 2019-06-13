/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send_all
*/

#include <unistd.h>
#include "graph_commands.h"

void send_all_graphics(sock_list_t *list, const char *s)
{
    sock_node_t *node = list->start;
    zappy_client_t *cli;

    for (; node != NULL; node = node->next) {
        if (node->socket->type != CLIENT)
            continue;
        cli = node->socket->data;
        if (cli == NULL)
            continue;
        if (cli->cli_type != GRAPHICAL)
            continue;
        write(node->socket->fd, s, strlen(s));
    }
}
