/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** take
*/

#include "graph_commands.h"
#include "server.h"

void graph_send_ia_pdr(sock_list_t *list, ia_t *ia, ITEM_T item)
{
    char buff[4096] = {0};

    sprintf(buff, "pdr %d %d\n", ia->id, item);
    send_all_graphics(list, buff);
}

void cmd_ia_set(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    tile_t *tile = GET_TILE(GET_GAME(list), ia->x, ia->y);
    int id_item = cmd_ia_settake_parser(cli, arg);

    (void)zarg;
    if (id_item == -1 || !ia->inventory[id_item]) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    tile->items[id_item] += 1;
    ia->inventory[id_item] -= 1;
    graph_send_ia_pdr(list, ia, id_item);
    graph_send_ia_pin(list, ia);
    graph_send_tile_bct(list, tile);
    dprintf(cli->fd, "ok\n");
}
