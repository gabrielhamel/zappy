/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** sst
*/

#include "graph_commands.h"
#include "game.h"

void cmd_graph_sst(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    (void)list;
    (void)arg;
    dprintf(cli->fd, "sst %f", zarg->freq);
}
