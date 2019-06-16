/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** eject
*/

#include "graph_commands.h"
#include "ia_commands.h"

static void send_res(sock_list_t *list, sock_t *cli, size_t nb)
{
    char buff[4096] = {0};

    if (nb == 0)
        dprintf(cli->fd, "ko\n");
    else {
        dprintf(cli->fd, "ok\n");
        sprintf(buff, "pex %d\n", cli->fd);
        send_all_graphics(list, buff);
    }
}

static void eject(sock_list_t *list, ia_t *ejecter, ia_t *ejected)
{
    int k = 0;

    ia_move(list, ejected, ejecter->ori);
    if (ejecter->ori == NORTH)
        k = get_direction(ejected, ZERO, NEGATIVE);
    if (ejecter->ori == EAST)
        k = get_direction(ejected, NEGATIVE, ZERO);
    if (ejecter->ori == SOUTH)
        k = get_direction(ejected, ZERO, POSITIVE);
    if (ejecter->ori == WEAST)
        k = get_direction(ejected, POSITIVE, ZERO);
    dprintf(ejected->id, "eject: %d\n", k);
}

void cmd_ia_eject(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    zappy_client_t *client;
    ia_t *me = ZAPPY_CLIENT(cli)->client.ia;
    size_t nb = 0;
    ia_t *ia;

    (void)arg;
    (void)zarg;
    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia->x != me->x || ia->y != me->y || ia == me)
            continue;
        nb++;
        eject(list, me, ia);
    }
    send_res(list, cli, nb);
}
