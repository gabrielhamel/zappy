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

static bool tile_have_player(sock_list_t *list, tile_t *tile)
{
    zappy_client_t *client;
    ia_t *ia;

    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia->x == tile->x && ia->y == tile->y)
            return true;
    }
    return false;
}

static bool tile_have_item(ITEM_T item, tile_t *tile)
{
    if (tile->items[item] != 0)
        return true;
    return false;
}

static void tile_to_string(sock_list_t *list, tile_t *tile, char *buff)
{
    bool first = false;

    if (tile_have_player(list, tile)) {
        sprintf(buff, "player");
        first = true;
    }
    for (ITEM_T item = FOOD; item < N_ITEMS; item++) {
        if (tile_have_item(item, tile) == false)
            continue;
        if (first == false)
            first = true;
        else
            sprintf(buff + strlen(buff), " ");
        sprintf(buff + strlen(buff), "%s", objects[item]);
    }
}

void cmd_ia_look(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    char buff[4096] = {0};

    (void)arg;
    (void)zarg;
}
