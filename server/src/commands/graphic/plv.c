/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** plv
*/

#include "graph_commands.h"

void cmd_graph_plv(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia;

    (void)zarg;
    if (array_lenght(arg) != 2) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    ia = get_player_by_id(atoi(arg[1]), list);
    if (ia == NULL) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    dprintf(cli->fd, "plv %d %d\n", ia->id, ia->level);
}
