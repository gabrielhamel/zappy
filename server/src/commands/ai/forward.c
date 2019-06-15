/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** forward
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_forward(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    char buff[4096] = {0};

    (void)arg;
    switch (ia->ori) {
        case NORTH:
            ia->y = (ia->y + 1) % zarg->height;
        break;
        case EAST:
            ia->x = (ia->x + 1) % zarg->width;
        break;
        case SOUTH:
            ia->y += (ia->y == 0) ? (int)zarg->height - 1 : -1;
        break;
        case WEAST:
            ia->x += (ia->x == 0) ? (int)zarg->width - 1 : -1;
        break;
    }
    dprintf(cli->fd, "ok\n");
    sprintf(buff, "ppo %d %ld %ld %d\n", ia->id, ia->x, ia->y, ia->ori);
    send_all_graphics(list, buff);
}
