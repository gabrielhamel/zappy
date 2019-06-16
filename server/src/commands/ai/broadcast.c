/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Broadcast
*/

#include "graph_commands.h"
#include "server.h"

void graph_send_broadcast(sock_list_t *list, ia_t *ia, const char *str)
{
    char buff[4096] = {0};

    sprintf(buff, "pbc %d %s\n", ia->id, str);
    send_all_graphics(list, buff);
}

static void broadcast(map_t *map, ia_t *sender, ia_t *receiver, const char *s)
{
    int dir = 0;

    dprintf(receiver->id, "message %d, %s\n", dir, s);
}

void cmd_ia_broad(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *me = ZAPPY_CLIENT(cli)->client.ia;
    ia_t *ia;
    zappy_client_t *client;

    (void)zarg;
    if (array_lenght(arg) < 2) {
        dprintf(cli->fd, "ok\n");
        return;
    }
    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia == me)
            continue;
        broadcast(&GET_GAME(list)->map, me, ia, arg[1]);
    }
    graph_send_broadcast(list, me, arg[1]);
    dprintf(cli->fd, "ok\n");
}
