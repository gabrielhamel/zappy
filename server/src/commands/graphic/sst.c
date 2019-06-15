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
    char buff[4096] = {0};
    float nb;

    if (array_lenght(arg) < 2) {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    nb = atof(arg[1]);
    if (nb <= 0) {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    zarg->freq = nb;
    dprintf(cli->fd, "sst %.0f\n", zarg->freq);
    sprintf(buff, "sgt %.0f\n", zarg->freq);
    send_all_graphics(list, buff);
}
