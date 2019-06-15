/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** right
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_right(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;

    ia->ori++;
    if (ia->ori > WEAST)
        ia->ori = NORTH;
    graph_send_ia_ppo(list, ia);
    dprintf(cli->fd, "ok\n");
}
