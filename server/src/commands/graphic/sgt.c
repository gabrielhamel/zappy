/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** sgt
*/

#include "graph_commands.h"
#include "game.h"

void cmd_send_sgt(sock_t *cli, zarg_t *zarg)
{
    dprintf(cli->fd, "sgt %.0f\n", zarg->freq);
}

void cmd_graph_sgt(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    (void)list;

    if (array_lenght(arg) != 2) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    zarg->freq = atof(arg[1]);
    dprintf(cli->fd, "sgt %.0f\n", zarg->freq);
}
