/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** take
*/

#include "graph_commands.h"
#include "server.h"

void graph_send_ia_pgt(sock_list_t *list, ia_t *ia, ITEM_T item)
{
    char buff[4096] = {0};

    sprintf(buff, "pgt %d %d\n", ia->id, item);
    send_all_graphics(list, buff);
}

void cmd_ia_take(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    tile_t *tile = GET_TILE(GET_GAME(list), ia->x, ia->y);
    int id_item = cmd_ia_settake_parser(cli, arg);

    if (id_item == -1 || !tile->items[id_item]) {
        sock_write(cli, "ko\n");
        return;
    }
    tile->items[id_item] -= 1;
    ia->inventory[id_item] += 1;
    graph_send_ia_pgt(list, ia, id_item);
    graph_send_ia_pin(list, ia);
    graph_send_tile_bct(list, tile);
    tile = &GET_GAME(list)->map.graph[rand() %
    zarg->height][rand() % zarg->width];
    tile->items[id_item] += 1;
    graph_send_tile_bct(list, tile);
    sock_write(cli, "ok\n");
}
