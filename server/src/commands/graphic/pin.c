/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** plv
*/

#include "graph_commands.h"
#include "utils.h"

void graph_send_ia_pin(sock_list_t *list, ia_t *ia)
{
    char buff[4096] = {0};
    int *inv = ia->inventory;

    sprintf(buff, "pin %d %ld %ld %d %d %d %d %d %d %d\n", ia->id, ia->x, ia->y,
    inv[0], inv[1], inv[2], inv[3], inv[4], inv[5], inv[6]);
    send_all_graphics(list, buff);
}

void cmd_graph_pin(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia;
    int *inv;

    (void)zarg;
    if (array_lenght(arg) < 2 || !is_num(arg[1])) {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    ia = get_player_by_id(atoi(arg[1]), list);
    if (ia == NULL) {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    inv = ia->inventory;
    dprintf(cli->fd, "pin %d %ld %ld %d %d %d %d %d %d %d\n", ia->id,
    ia->x, ia->y, inv[0], inv[1], inv[2], inv[3], inv[4], inv[5], inv[6]);
}
