/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** left
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_left(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;

    (void)arg;
    (void)zarg;
    ia->ori--;
    if (ia->ori < NORTH)
        ia->ori = WEAST;
    graph_send_ia_ppo(list, ia);
    dprintf(cli->fd, "ok\n");
}
