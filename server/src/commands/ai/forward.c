/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** forward
*/

#include "graph_commands.h"
#include "server.h"

void graph_send_ia_ppo(sock_list_t *list, ia_t *ia)
{
    char buff[4096] = {0};

    sprintf(buff, "ppo %d %ld %ld %d\n", ia->id, ia->x, ia->y, ia->ori);
    send_all_graphics(list, buff);
}

void ia_move(sock_list_t *list, ia_t *ia, facing_t ori)
{
    map_t *map = &GET_GAME(list)->map;

    switch (ori) {
        case NORTH:
            ia->y = (ia->y + 1) % map->h;
        break;
        case EAST:
            ia->x = (ia->x + 1) % map->w;
        break;
        case SOUTH:
            ia->y += (ia->y == 0) ? (int)map->h - 1 : -1;
        break;
        case WEAST:
            ia->x += (ia->x == 0) ? (int)map->w - 1 : -1;
        break;
    }
    graph_send_ia_ppo(list, ia);
}

void cmd_ia_forward(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;

    (void)arg;
    (void)zarg;
    ia_move(list, ia, ia->ori);
    sock_write(cli, "ok\n");
}
