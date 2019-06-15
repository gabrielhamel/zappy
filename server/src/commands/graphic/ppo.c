/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ppo
*/

#include "graph_commands.h"
#include "utils.h"

void cmd_graph_ppo(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
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
    dprintf(cli->fd, "ppo %d %ld %ld %d\n", ia->id, ia->x, ia->y, ia->ori);
}
