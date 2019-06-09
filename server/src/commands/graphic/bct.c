/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** btc
*/

#include "graph_commands.h"
#include "game.h"

void cmd_graph_bct(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    tile_t *tile;

    (void)zarg;
    if (array_lenght(arg) != 3)
        dprintf(cli->fd, "ko\n");
    tile = GET_TILE(GET_GAME(list), atoi(arg[1]), atoi(arg[2]));
    dprintf(cli->fd, "bct %s %s %hd %hd %hd %hd %hd %hd %hd\n", arg[1],
    arg[2], tile->items[0], tile->items[1], tile->items[2], tile->items[3],
    tile->items[4], tile->items[5], tile->items[6]);
}
