/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** btc
*/

#include "graph_commands.h"
#include "game.h"

void cmd_graph_bct_all(sock_t *cli, sock_list_t *list)
{
    game_t *game = GET_GAME(list);
    map_t *map = &(game->map);
    tile_t *tile;

    for (size_t x = 0; x < map->w; x++)
        for (size_t y = 0; y < map->h; y++) {
            tile = GET_TILE(game, x, y);
            dprintf(cli->fd, "bct %ld %ld %hd %hd %hd %hd %hd %hd %hd\n", x, y,
            tile->items[0], tile->items[1], tile->items[2], tile->items[3],
            tile->items[4], tile->items[5], tile->items[6]);
        }
}

void cmd_graph_bct(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    tile_t *tile;

    (void)zarg;
    if (array_lenght(arg) != 3
        || (unsigned int)atoi(arg[1]) >= GET_GAME(list)->map.w
        || (unsigned int)atoi(arg[2]) >= GET_GAME(list)->map.h) {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    tile = GET_TILE(GET_GAME(list), atoi(arg[1]), atoi(arg[2]));
    dprintf(cli->fd, "bct %s %s %hd %hd %hd %hd %hd %hd %hd\n", arg[1],
    arg[2], tile->items[0], tile->items[1], tile->items[2], tile->items[3],
    tile->items[4], tile->items[5], tile->items[6]);
}
