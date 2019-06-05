/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** btc
*/

#include "graph_commands.h"

void cmd_graph_btc(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    dprintf(cli->fd, "btc %s %s %d %d %d %d %d %d\n", arg[0], arg[1]);
}
