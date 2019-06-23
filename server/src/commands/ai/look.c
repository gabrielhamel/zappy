/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** look
*/

#include "graph_commands.h"
#include "server.h"
#include "item.h"

static const char *objects[N_ITEMS] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

static int tile_have_player(sock_list_t *list, tile_t *tile)
{
    zappy_client_t *client;
    ia_t *ia;
    int nb = 0;

    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia->x == tile->x && ia->y == tile->y)
            nb++;
    }
    return nb;
}

static int tile_have_item(ITEM_T item, tile_t *tile)
{
    if (tile->items[item] != 0)
        return tile->items[item];
    return 0;
}

static void tile_to_string(sock_list_t *list, tile_t *tile, char *buff)
{
    int player = tile_have_player(list, tile);
    int items;

    for (int i = 0; i < player; i++)
        sprintf(buff, " player");
    for (ITEM_T item = FOOD; item < N_ITEMS; item++) {
        items = tile_have_item(item, tile);
        for (int i = 0; i < items; i++)
            sprintf(buff + strlen(buff), " %s", objects[item]);
    }
}

static tile_t *get_tile_at(facing_t dir, tile_t *tile, facing_t player_facing)
{
    facing_t new_dir = (dir - 1 + player_facing - 1) % 4 + 1;

    if (new_dir == NORTH)
        return tile->bottom;
    else if (new_dir == EAST)
        return tile->right;
    else if (new_dir == SOUTH)
        return tile->top;
    else
        return tile->left;
}

void cmd_ia_look(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    tile_t *base = GET_TILE(GET_GAME(list), ia->x, ia->y);
    tile_t *tmp = base;
    char buff[4096] = {0};

    (void)arg;
    (void)zarg;
    sprintf(buff + strlen(buff), "[");
    for (int row = 0; row < ia->level + 1; row++) {
        for (int col = 0; col < 1 + 2 * row; col++) {
            tile_to_string(list, tmp, buff + strlen(buff));
            tmp = get_tile_at(EAST, tmp, ia->ori);
            if (!(row == ia->level && col == 2 * row))
                sprintf(buff + strlen(buff), ",");
        }
        base = get_tile_at(NORTH, base, ia->ori);
        base = get_tile_at(WEAST, base, ia->ori);
        tmp = base;
    }
    sprintf(buff + strlen(buff), " ]");
    sock_write(cli, "%s\n", buff);
}
