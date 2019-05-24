/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#include "graph_commands.h"

static graph_cmd_t cmd_g[] = {
    {"msz", cmd_graph_msz},
    {"bct", NULL},
    {"mct", NULL},
    {"tna", NULL},
    {"ppo", NULL},
    {"plv", NULL},
    {"pin", NULL}
};

void exec_graph_cmd(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g) && arg[0]; i++)
        if (arg[0] && !strcasecmp(cmd_g[i].name, arg[0]) && cmd_g[i].func != NULL) {
            cmd_g[i].func(cli, list, arg, zarg);
            return;
        }
        else if (arg[0] && !strcasecmp(cmd_g[i].name, arg[0])) {
            dprintf(cli->fd, "Not implemented\n");
            return;
        }
    dprintf(cli->fd, "suc\n");
}