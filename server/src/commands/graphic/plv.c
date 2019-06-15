/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** plv
*/

#include "graph_commands.h"
#include "utils.h"

void graph_send_ia_plv(sock_list_t *list, ia_t *ia)
{
    char buff[4096] = {0};

    sprintf(buff, "plv %d %d\n", ia->id, ia->level);
    send_all_graphics(list, buff);
}

void cmd_graph_plv(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia;

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
    dprintf(cli->fd, "plv %d %d\n", ia->id, ia->level);
}
