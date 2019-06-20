/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** inventory
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_inv(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    int *inv = ia->inventory;

    (void)arg;
    (void)list;
    (void)zarg;
    sock_write(cli, "[ food %d, linemate %d, deraumere %d, " \
    "sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
    inv[0], inv[1], inv[2], inv[3], inv[4], inv[5], inv[6]);
}
