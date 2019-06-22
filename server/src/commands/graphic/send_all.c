/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send_all
*/

#include <unistd.h>
#include <stdio.h>
#include "graph_commands.h"

void send_all_players(sock_t *graph, sock_list_t *list)
{
    sock_node_t *node = list->start;
    zappy_client_t *cli;
    ia_t *ia;

    for (; node != NULL; node = node->next) {
        if (node->socket->type != CLIENT)
            continue;
        cli = node->socket->data;
        if (cli == NULL)
            continue;
        if (cli->cli_type != IA)
            continue;
        ia = cli->client.ia;
        sock_write(graph, "pnw %d %ld %ld %d %d %s\n",
        ia->id, ia->x, ia->y, ia->ori, ia->level, ia->team->name);
    }
}

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
