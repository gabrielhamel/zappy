/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** take
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_take(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = (ia_t *)cli->data;
    tile_t *tile;
    int id_item;

    (void)zarg;
    id_item = cmd_ia_settake_parser(cli, arg);
    if (id_item == -1)
        return;
    tile = GET_TILE(GET_GAME(list), ia->x, ia->y);
    if (tile->items[id_item] > 0) {
        tile->items[id_item] -= 1;
        ia->inventory[id_item] += 1;
        graph_send_ia_ppo(list, ia);
        graph_send_ia_pin(list, ia);
        dprintf(cli->fd, "ok\n");
    }
    else {
        dprintf(cli->fd, "ko\n");
        return;
    }
}
