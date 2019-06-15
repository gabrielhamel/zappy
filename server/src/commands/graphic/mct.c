/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** mct
*/

#include "graph_commands.h"
#include "game.h"

void cmd_graph_mct(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    game_t *game = GET_GAME(list);
    tile_t *tile;

    (void)arg;
    (void)zarg;

    for (size_t y = 0; y < game->map.h; y++) {
        for (size_t x = 0; x < game->map.w; x++) {
            tile = GET_TILE(game, x, y);
            dprintf(cli->fd, "bct %lu %lu %hd %hd %hd %hd %hd %hd %hd\n", x,
            y, tile->items[0], tile->items[1], tile->items[2], tile->items[3],
            tile->items[4], tile->items[5], tile->items[6]);
        }
    }
}
