/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** msz
*/

#include "graph_commands.h"

void cmd_graph_msz(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    (void)list;
    (void)arg;
    sock_write(cli, "msz %d %d\n", zarg->width, zarg->height);
}
