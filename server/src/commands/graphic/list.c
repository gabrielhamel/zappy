/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#include "graph_commands.h"

static graph_cmd_t cmd_g[] = {
    {"msz", cmd_graph_msz},
    {"bct", cmd_graph_bct},
    {"mct", cmd_graph_mct},
    {"tna", cmd_graph_tna},
    {"ppo", cmd_graph_ppo},
    {"plv", cmd_graph_plv},
    {"pin", cmd_graph_pin},
    {"sgt", cmd_graph_sgt},
    {"sst", cmd_graph_sst}
};

void exec_graph_cmd(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g) && arg[0]; i++)
        if (arg[0] && !strcmp(cmd_g[i].name, arg[0]) &&
        cmd_g[i].func != NULL) {
            cmd_g[i].func(cli, list, arg, zarg);
            return;
        }
    sock_write(cli, "suc\n");
}
